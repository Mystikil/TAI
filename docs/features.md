# Feature Overview

This document summarizes the main gameplay systems found in this repository. It includes the primary data structures, important enums and notable functions related to skills, professions (vocations), spells and various scripted actions.

## Skills

Player skills are defined by `enum skills_t` in `src/enums.h`. The list includes both combat skills and profession skills:

```
SKILL_FIST, SKILL_CLUB, SKILL_SWORD, SKILL_AXE,
SKILL_DISTANCE, SKILL_SHIELD, SKILL_FISHING,
SKILL_BLACKSMITHING, SKILL_FARMING, SKILL_JEWELCRAFTING,
SKILL_MAGLEVEL, SKILL_LEVEL
```

Additional skill-related types:

- `skillsid_t` (in `src/player.h`) differentiates between current level, tries and progress percentage.
- `SpecialSkills_t` and `stats_t` (in `src/enums.h`) track attributes like critical hit chance or mana points.

Key functions on the `Player` class managing skills include:

- `getSkillLevel`, `getSkillPercent`
- `addSkillAdvance`, `addOfflineTrainingTries`
- `getSpecialSkill`, `setVarSkill`

## Professions (Vocations)

Professions are represented by the `Vocation` class in `src/vocation.h`. Each vocation defines base stats such as HP gain, mana gain and attack speed. The `Vocations` container loads all definitions from XML.

Notable Vocation members:

- `getReqSkillTries`, `getReqMana`
- `getAttackSpeed`, `getBaseSpeed`
- `getFromVocation` (promotion tree)

The active profession for a player is accessed via `Player::getVocation()`.

## Spells

Spells are implemented in `src/spells.*`. There are two main spell types:

- `InstantSpell` – cast immediately via a talkaction (e.g. words like *exori*).
- `RuneSpell` – cast by using a rune item.

Common functionality is provided by the `Spell` base class. Important enums:

```
SpellGroup_t  – damage or utility groupings
SpellType_t   – instant vs rune
CombatType_t  – physical, fire, energy, etc.
```

Key functions:

- `playerSaySpell` – processes spoken spell words
- `Spell::castSpell`, `Spell::postCastSpell`
- `Player::learnInstantSpell`, `Player::forgetInstantSpell`

Spells are defined through Lua scripts under `data/scripts/spells/`.

## Actions

Context-based item interactions are registered in `data/actions/actions.xml`. Each entry links an item or item range to a Lua script.

Examples include:

- Enchanting gems (`others/enchanting.lua`)
- Quest triggers (`quests/quests.lua` and `quests/annihilator.lua`)
- Tools such as fishing, pickaxes or ropes under `tools/`
- Alchemy shelf usage (`others/alchemy.lua`)

Scripts reside in `data/actions/scripts/` and implement the behavior through the `onUse` function.

## Enumerations and Utility Types

The engine uses numerous enums to control gameplay. Highlights from `src/enums.h` include:

- `CombatParam_t`, `ConditionType_t` – configure combat and status effects
- `VipStatus_t`, `MarketAction_t`, `MarketOfferState_t` – various system states
- `ReturnValue` – error codes returned by item and spell actions

Other utility structs such as `Outfit_t`, `ShopInfo`, `MarketOffer` describe data passed between systems.

## Additional Functionality

- Player state changes: `Player::changeHealth`, `Player::changeMana`, `Player::changeSoul`
- Trading and shops: `Player::setShopOwner`, `Player::openShopWindow`
- Party and guild operations: `Player::getGuild`, `Player::addPartyInvitation`

These functions, together with the enums and scripts above, compose the main feature set of the game server.

\nSee also [AI scripting](ai_scripting.md) for details on customizing monster and NPC behavior.
