# Alchemy System

This system lets players brew potions using common loot items. Recipes are defined in a Lua configuration file so new combinations can be added without touching the main script.

## Files

- `data/scripts/alchemy/recipes.lua` – defines available recipes.
- `data/scripts/actions/others/alchemy.lua` – handles player interaction.
- `data/actions/actions.xml` – registers the alchemy shelf action.

## Usage

1. Put the ingredients into an **alchemy shelf** (item IDs `37044` or `37045`).
2. Use the shelf. If the contents match a recipe, the items are consumed and the shelf will produce the result potion.

## Adding Recipes

Edit `data/scripts/alchemy/recipes.lua`. Each recipe entry has:

```lua
{
    ingredients = { -- list of item IDs
        2148, 2671
    },
    result = 7618,      -- item ID of the created potion
    message = "You brew a health potion." -- optional text shown to the player
}
```

Include any number of ingredient IDs. The order of ingredients inside the shelf does not matter, but the shelf must contain exactly those items and nothing else.

