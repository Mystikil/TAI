#define BOOST_TEST_MODULE spell_registry

#include "../otpch.h"
#include "../spell_registry.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(load_spells_from_json)
{
    const std::string json = R"([
        {
            "id": 1,
            "name": "Intense Healing",
            "words": "exura gran",
            "type": "instant",
            "group": "healing",
            "level": 20,
            "mana": 70
        }
    ])";

    SpellRegistry registry;
    BOOST_TEST(registry.loadFromJsonString(json));
    const SpellDefinition* def = registry.getSpell(1);
    BOOST_REQUIRE(def != nullptr);
    BOOST_TEST(def->name == "Intense Healing");
    BOOST_TEST(def->words == "exura gran");
    BOOST_TEST(def->level == 20u);
    BOOST_TEST(def->mana == 70u);
}

