#pragma once

#include <unordered_map>
#include <string>
#include <boost/json.hpp>

struct SpellDefinition {
    uint16_t id = 0;
    std::string name;
    std::string words;
    std::string type;
    std::string group;
    uint32_t level = 0;
    uint32_t mana = 0;
};

class SpellRegistry {
public:
    bool loadFromJsonFile(const std::string& path);
    bool loadFromJsonString(std::string_view json);

    const SpellDefinition* getSpell(uint16_t id) const;

private:
    std::unordered_map<uint16_t, SpellDefinition> spells;
};

