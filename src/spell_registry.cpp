#include "otpch.h"

#include "spell_registry.h"

#include <fstream>
#include <boost/json/src.hpp>

bool SpellRegistry::loadFromJsonString(std::string_view json)
{
    spells.clear();
    boost::json::value root = boost::json::parse(json);
    if (!root.is_array()) {
        return false;
    }
    for (const auto& item : root.as_array()) {
        if (!item.is_object()) {
            continue;
        }
        const auto& obj = item.as_object();
        SpellDefinition def;
        if (auto it = obj.if_contains("id")) {
            def.id = static_cast<uint16_t>(boost::json::value_to<uint64_t>(*it));
        }
        if (auto it = obj.if_contains("name")) {
            def.name = boost::json::value_to<std::string>(*it);
        }
        if (auto it = obj.if_contains("words")) {
            def.words = boost::json::value_to<std::string>(*it);
        }
        if (auto it = obj.if_contains("type")) {
            def.type = boost::json::value_to<std::string>(*it);
        }
        if (auto it = obj.if_contains("group")) {
            def.group = boost::json::value_to<std::string>(*it);
        }
        if (auto it = obj.if_contains("level")) {
            def.level = static_cast<uint32_t>(boost::json::value_to<uint64_t>(*it));
        }
        if (auto it = obj.if_contains("mana")) {
            def.mana = static_cast<uint32_t>(boost::json::value_to<uint64_t>(*it));
        }
        spells.emplace(def.id, std::move(def));
    }
    return true;
}

bool SpellRegistry::loadFromJsonFile(const std::string& path)
{
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }
    std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return loadFromJsonString(data);
}

const SpellDefinition* SpellRegistry::getSpell(uint16_t id) const
{
    auto it = spells.find(id);
    if (it == spells.end()) {
        return nullptr;
    }
    return &it->second;
}

