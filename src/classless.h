#ifndef FS_CLASSLESS_H
#define FS_CLASSLESS_H

#include <cstdint>

enum class StatAttribute : uint8_t {
    HEALTH,
    MANA,
    CAPACITY,
    LAST
};

struct ClasslessStats {
    uint16_t health = 0;
    uint16_t mana = 0;
    uint16_t capacity = 0;

    uint16_t& get(StatAttribute attr)
    {
        switch (attr) {
            case StatAttribute::HEALTH:
                return health;
            case StatAttribute::MANA:
                return mana;
            case StatAttribute::CAPACITY:
                return capacity;
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
            default:
                return 0;
        }
    }
};

#endif // FS_CLASSLESS_H
