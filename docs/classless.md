# Classless System

This repository includes an experimental classless character progression mode.
When enabled through `enableClasslessSystem` in `config.lua`, players no longer
gain stats from predefined vocations. Instead, each level grants a number of
free points (configured by `pointsPerLevel`) which can be spent on custom
attributes.

Currently only health, mana and capacity can be increased. Points are stored in
`Player::statPoints` and applied using `Player::spendStatPoint`. The feature is
not integrated with spells or equipment restrictions and should be considered a
work in progress.
