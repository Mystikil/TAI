// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#include "otpch.h"

#include "otserv.h"

#include "configmanager.h"
#include "databasemanager.h"
#include "databasetasks.h"
#include "game.h"
#include "http/http.h"
#include "iomarket.h"
#include "monsters.h"
#include "outfit.h"
#include "protocollogin.h"
#include "protocolold.h"
#include "protocolstatus.h"
#include "rsa.h"
#include "scheduler.h"
#include "script.h"
#include "scriptmanager.h"
#include "server.h"

#include <fstream>

#if __has_include("gitmetadata.h")
#include "gitmetadata.h"
#endif

DatabaseTasks g_databaseTasks;
Dispatcher g_dispatcher;
Scheduler g_scheduler;

Game g_game;
Monsters g_monsters;
Vocations g_vocations;
extern Scripts* g_scripts;

std::mutex g_loaderLock;
std::condition_variable g_loaderSignal;
std::unique_lock<std::mutex> g_loaderUniqueLock(g_loaderLock);

namespace {

void startupErrorMessage(const std::string& errorStr)
{
	fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "> ERROR: {:s}\n", errorStr);
	g_loaderSignal.notify_all();
}

static bool loadConfiguration()
{
        // check if config.lua or config.lua.dist exist
        const std::string& configFile = getString(ConfigManager::CONFIG_FILE);
        std::ifstream c_test("./" + configFile);
        if (!c_test.is_open()) {
                std::ifstream config_lua_dist("./config.lua.dist");
                if (config_lua_dist.is_open()) {
                        std::cout << ">> copying config.lua.dist to " << configFile << std::endl;
                        std::ofstream config_lua(configFile);
                        config_lua << config_lua_dist.rdbuf();
                        config_lua.close();
                        config_lua_dist.close();
                }
        } else {
                c_test.close();
        }

        std::cout << ">> Loading config" << std::endl;
        if (!ConfigManager::load()) {
                startupErrorMessage("Unable to load " + configFile + "!");
                return false;
        }

#ifdef _WIN32
        const std::string& defaultPriority = getString(ConfigManager::DEFAULT_PRIORITY);
        if (caseInsensitiveEqual(defaultPriority, "high")) {
                SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
        } else if (caseInsensitiveEqual(defaultPriority, "above-normal")) {
                SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
        }
#endif

        std::cout << ">> Loading RSA key " << std::endl;
        try {
                std::ifstream key{"key.pem"};
                std::string pem{std::istreambuf_iterator<char>{key}, std::istreambuf_iterator<char>{}};
                tfs::rsa::loadPEM(pem);
        } catch (const std::exception& e) {
                startupErrorMessage(e.what());
                return false;
        }

        return true;
}

static bool setupDatabase()
{
        std::cout << ">> Establishing database connection..." << std::flush;

        if (!Database::getInstance().connect()) {
                startupErrorMessage("Failed to connect to database.");
                return false;
        }

        std::cout << " MySQL " << Database::getClientVersion() << std::endl;

        std::cout << ">> Running database manager" << std::endl;

        if (!DatabaseManager::isDatabaseSetup()) {
                startupErrorMessage("The database you have specified in config.lua is empty, please import the schema.sql to your database.");
                return false;
        }

        g_databaseTasks.start();

        DatabaseManager::updateDatabase();

        if (getBoolean(ConfigManager::OPTIMIZE_DATABASE) && !DatabaseManager::optimizeTables()) {
                std::cout << "> No tables were optimized." << std::endl;
        }

        return true;
}

static bool loadServerData()
{
        std::cout << ">> Loading vocations" << std::endl;
        if (std::ifstream is{"data/XML/vocations.xml"}; !g_vocations.loadFromXml(is, "data/XML/vocations.xml")) {
                startupErrorMessage("Unable to load vocations!");
                return false;
        }

        std::cout << ">> Loading items... ";
        if (!Item::items.loadFromOtb("data/items/items.otb")) {
                startupErrorMessage("Unable to load items (OTB)!");
                return false;
        }
        std::cout << fmt::format("OTB v{:d}.{:d}.{:d}", Item::items.majorVersion, Item::items.minorVersion,
                                 Item::items.buildNumber)
                  << std::endl;

        if (!Item::items.loadFromXml()) {
                startupErrorMessage("Unable to load items (XML)!");
                return false;
        }

        std::cout << ">> Loading script systems" << std::endl;
        if (!ScriptingManager::getInstance().loadScriptSystems()) {
                startupErrorMessage("Failed to load script systems");
                return false;
        }

        std::cout << ">> Loading lua scripts" << std::endl;
        if (!g_scripts->loadScripts("scripts", false, false)) {
                startupErrorMessage("Failed to load lua scripts");
                return false;
        }

        std::cout << ">> Loading monsters" << std::endl;
        if (!g_monsters.loadFromXml()) {
                startupErrorMessage("Unable to load monsters!");
                return false;
        }

        std::cout << ">> Loading lua monsters" << std::endl;
        if (!g_scripts->loadScripts("monster", false, false)) {
                startupErrorMessage("Failed to load lua monsters");
                return false;
        }

        std::cout << ">> Loading outfits" << std::endl;
        if (!Outfits::getInstance().loadFromXml()) {
                startupErrorMessage("Unable to load outfits!");
                return false;
        }

        std::cout << ">> Checking world type... " << std::flush;
        std::string worldType = boost::algorithm::to_lower_copy(getString(ConfigManager::WORLD_TYPE));
        if (worldType == "pvp") {
                g_game.setWorldType(WORLD_TYPE_PVP);
        } else if (worldType == "no-pvp") {
                g_game.setWorldType(WORLD_TYPE_NO_PVP);
        } else if (worldType == "pvp-enforced") {
                g_game.setWorldType(WORLD_TYPE_PVP_ENFORCED);
        } else {
                std::cout << std::endl;
                startupErrorMessage(fmt::format("Unknown world type: {:s}, valid world types are: pvp, no-pvp and pvp-enforced.",
                                getString(ConfigManager::WORLD_TYPE)));
                return false;
        }
        std::cout << boost::algorithm::to_upper_copy(worldType) << std::endl;

        std::cout << ">> Loading map" << std::endl;
        if (!g_game.loadMainMap(getString(ConfigManager::MAP_NAME))) {
                startupErrorMessage("Failed to load map");
                return false;
        }

        return true;
}

static void startNetworkServices(ServiceManager* services)
{
        services->add<ProtocolGame>(static_cast<uint16_t>(getNumber(ConfigManager::GAME_PORT)));
        services->add<ProtocolLogin>(static_cast<uint16_t>(getNumber(ConfigManager::LOGIN_PORT)));
        services->add<ProtocolStatus>(static_cast<uint16_t>(getNumber(ConfigManager::STATUS_PORT)));
        services->add<ProtocolOld>(static_cast<uint16_t>(getNumber(ConfigManager::LOGIN_PORT)));

        tfs::http::start(getString(ConfigManager::IP), getNumber(ConfigManager::HTTP_PORT),
                         getNumber(ConfigManager::HTTP_WORKERS));
}

void mainLoader(ServiceManager* services)
{
        g_game.setGameState(GAME_STATE_STARTUP);

        srand(static_cast<unsigned int>(OTSYS_TIME()));
#ifdef _WIN32
        SetConsoleTitle(STATUS_SERVER_NAME);

        // fixes a problem with escape characters not being processed in Windows consoles
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif

        printServerVersion();

        if (!loadConfiguration()) {
                return;
        }

        if (!setupDatabase()) {
                return;
        }

        if (!loadServerData()) {
                return;
        }

        std::cout << ">> Initializing gamestate" << std::endl;
        g_game.setGameState(GAME_STATE_INIT);

        startNetworkServices(services);

	RentPeriod_t rentPeriod;
	std::string strRentPeriod = boost::algorithm::to_lower_copy(getString(ConfigManager::HOUSE_RENT_PERIOD));

	if (strRentPeriod == "yearly") {
		rentPeriod = RENTPERIOD_YEARLY;
	} else if (strRentPeriod == "weekly") {
		rentPeriod = RENTPERIOD_WEEKLY;
	} else if (strRentPeriod == "monthly") {
		rentPeriod = RENTPERIOD_MONTHLY;
	} else if (strRentPeriod == "daily") {
		rentPeriod = RENTPERIOD_DAILY;
	} else {
		rentPeriod = RENTPERIOD_NEVER;
	}

	g_game.map.houses.payHouses(rentPeriod);

	IOMarket::checkExpiredOffers();
	IOMarket::getInstance().updateStatistics();

	std::cout << ">> Loaded all modules, server starting up..." << std::endl;

#ifndef _WIN32
	if (getuid() == 0 || geteuid() == 0) {
		std::cout << "> Warning: " << STATUS_SERVER_NAME
		          << " has been executed as root user, please consider running it as a normal user." << std::endl;
	}
#endif

	g_game.start(services);
	g_game.setGameState(GAME_STATE_NORMAL);
	g_loaderSignal.notify_all();
}

[[noreturn]] void badAllocationHandler()
{
	// Use functions that only use stack allocation
	puts("Allocation failed, server out of memory.\nDecrease the size of your map or compile in 64 bits mode.\n");
	getchar();
	exit(-1);
}

} // namespace

void startServer()
{
	// Setup bad allocation handler
	std::set_new_handler(badAllocationHandler);

	ServiceManager serviceManager;

	g_dispatcher.start();
	g_scheduler.start();

	g_dispatcher.addTask([services = &serviceManager]() { mainLoader(services); });

	g_loaderSignal.wait(g_loaderUniqueLock);

	if (serviceManager.is_running()) {
		std::cout << ">> " << getString(ConfigManager::SERVER_NAME) << " Server Online!" << std::endl << std::endl;
		serviceManager.run();
	} else {
		std::cout << ">> No services running. The server is NOT online." << std::endl;
		g_scheduler.shutdown();
		g_databaseTasks.shutdown();
		g_dispatcher.shutdown();
	}

	g_scheduler.join();
	g_databaseTasks.join();
	g_dispatcher.join();
}

void printServerVersion()
{
#if defined(GIT_RETRIEVED_STATE) && GIT_RETRIEVED_STATE
	std::cout << STATUS_SERVER_NAME << " - Version " << GIT_DESCRIBE << std::endl;
	std::cout << "Git SHA1 " << GIT_SHORT_SHA1 << " dated " << GIT_COMMIT_DATE_ISO8601 << std::endl;
#if GIT_IS_DIRTY
	std::cout << "*** DIRTY - NOT OFFICIAL RELEASE ***" << std::endl;
#endif
#else
	std::cout << STATUS_SERVER_NAME << " - Version " << STATUS_SERVER_VERSION << std::endl;
#endif
	std::cout << std::endl;

	std::cout << "Compiled with " << BOOST_COMPILER << std::endl;
	std::cout << "Compiled on " << __DATE__ << ' ' << __TIME__ << " for platform ";
#if defined(__amd64__) || defined(_M_X64)
	std::cout << "x64" << std::endl;
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_)
	std::cout << "x86" << std::endl;
#elif defined(__arm__)
	std::cout << "ARM" << std::endl;
#else
	std::cout << "unknown" << std::endl;
#endif
#if defined(LUAJIT_VERSION)
	std::cout << "Linked with " << LUAJIT_VERSION << " for Lua support" << std::endl;
#else
	std::cout << "Linked with " << LUA_RELEASE << " for Lua support" << std::endl;
#endif
	std::cout << std::endl;

	std::cout << "A server developed by " << STATUS_SERVER_DEVELOPERS << std::endl;
	std::cout << "Visit our forum for updates, support, and resources: https://otland.net/." << std::endl;
	std::cout << std::endl;
}
