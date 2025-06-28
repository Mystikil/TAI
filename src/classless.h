#ifndef FS_CLASSLESS_H
#define FS_CLASSLESS_H

#include <cstdint>

enum class StatAttribute : uint8_t {
    HEALTH,
    MANA,
    CAPACITY,
    STRENGTH,
    AGILITY,
    VITALITY,
    INTELLIGENCE,
    LUCK,
    CHARISMA,
    SPIRIT,
    LAST
};

struct ClasslessStats {
    uint16_t health = 0;
    uint16_t mana = 0;
    uint16_t capacity = 0;
    uint16_t strength = 0;
    uint16_t agility = 0;
    uint16_t vitality = 0;
    uint16_t intelligence = 0;
    uint16_t luck = 0;
    uint16_t charisma = 0;
    uint16_t spirit = 0;

    uint16_t& get(StatAttribute attr)
    {
        switch (attr) {
            case StatAttribute::HEALTH:
                return health;
            case StatAttribute::MANA:
                return mana;
            case StatAttribute::CAPACITY:
                return capacity;
            case StatAttribute::STRENGTH:
                return strength;
            case StatAttribute::AGILITY:
                return agility;
            case StatAttribute::VITALITY:
                return vitality;
            case StatAttribute::INTELLIGENCE:
                return intelligence;
            case StatAttribute::LUCK:
                return luck;
            case StatAttribute::CHARISMA:
                return charisma;
            case StatAttribute::SPIRIT:
                return spirit;
            default:
                return health; // fallback
        }
    }

    uint16_t get(const StatAttribute attr) const
    {
        switch (attr) {
            case StatAttribute::HEALTH:
                return health;
            case StatAttribute::MANA:
                return mana;
            case StatAttribute::CAPACITY:
                return capacity;
            case StatAttribute::STRENGTH:
                return strength;
            case StatAttribute::AGILITY:
                return agility;
            case StatAttribute::VITALITY:
                return vitality;
            case StatAttribute::INTELLIGENCE:
                return intelligence;
            case StatAttribute::LUCK:
                return luck;
            case StatAttribute::CHARISMA:
                return charisma;
            case StatAttribute::SPIRIT:
                return spirit;
            default:
                return 0;
        }
    }
};

#endif // FS_CLASSLESS_H
