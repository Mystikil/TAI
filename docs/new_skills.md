# Additional Skills

This project introduces a range of extra skills beyond the default combat set. They enable new profession and exploration mechanics. Each skill has suggested item interactions or creatures already present in the repository.

## List of Skills

- **Alchemy** – Brew powerful potions and poisons. Uses the existing alchemy recipes in `data/scripts/alchemy/recipes.lua`. Bottles, herbs and rare monster drops can all be combined for unique effects.
- **Cooking** – Prepare food with short term buffs. Different meats or vegetables yield dishes that restore health, mana or grant temporary bonuses.
- **Mining** – Use a pickaxe on rocks to collect ores and crystals. Iron Ore and other minerals from `data/items/items.xml` are produced depending on the node.
- **Woodcutting** – Chop down tree items to gather logs. Sturdy trees provide more wood while weaker bushes might only yield twigs.
- **Carpentry** – Turn lumber into furniture or wooden weapons. Works together with items crafted from woodcutting.
- **Taming** – Capture wild animals with items from `data/scripts/actions/others/taming.lua`. Examples include the bear, boar, undead cavebear, tin lizard and ladybug.
- **Survival** – Improves gathering rates for foraged items such as berries or mushrooms found on the map.
- **First Aid** – Allows players to bandage themselves or others, restoring a small amount of health. Bandage items increase in potency with skill level.
- **Tracking** – Reveal recent creature activity. Higher levels highlight monster footsteps or show the direction of nearby players.
- **Thievery** – Enables stealing low value items from NPCs or chests. Success rate is based on skill level and stealthy equipment.
- **Lockpicking** – Open locked doors and containers without a key. Iron and steel locks require higher skill.
- **Sailing** – Control boats or ships for faster travel. Different vessels grant travel speed or cargo advantages.
- **Cartography** – Create detailed maps. Exploring new areas improves the accuracy of your minimap and may uncover hidden locations.
- **Beast Mastery** – Grants bonuses when fighting or taming beasts. Creatures like bears, boars, dragonlings, ironblights and shock heads give extra experience when mastered.
- **Fletching** – Craft ammunition such as arrows or bolts from wood and feathers gathered via woodcutting and hunting.

## Item and Creature Ties

- **Mining Nodes** – Rocks or crystal formations drop Iron Ore and gems when mined. Rarer nodes have a chance to yield special crystals used by jewelcrafting.
- **Trees** – Different tree items provide varying amounts of wood for the woodcutting skill. Some rare trees may drop unique bark used in carpentry recipes.
- **Taming Items** – The taming script already defines usable objects like the slingshot or hunting horn. At least five creatures—bear, boar, undead cavebear, tin lizard and ladybug—can be captured with them.
- **Beast Mastery** – Fighting the listed tameable creatures grants bonus experience or loot at higher levels of this skill.
- **Crafted Goods** – Logs from woodcutting can be transformed via carpentry into bows or furniture. Ores from mining feed directly into blacksmithing or jewelcrafting recipes.

Each skill follows the same advancement logic as the existing ones: experience is tracked by the `Player` class and defined in `src/enums.h`. Scripts can check or increase these skills using the regular `getSkillLevel` and `addSkillAdvance` functions.
