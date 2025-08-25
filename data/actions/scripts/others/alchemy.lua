-- Alchemy system action

-- Load recipes if not already loaded
if not ALCHEMY_RECIPES then
    dofile('data/scripts/alchemy/recipes.lua')
end

local function matchRecipe(ids)
    table.sort(ids)
    for _, recipe in pairs(ALCHEMY_RECIPES) do
        local rids = { table.unpack(recipe.ingredients) }
        table.sort(rids)
        if #ids == #rids then
            local ok = true
            for i = 1, #rids do
                if rids[i] ~= ids[i] then
                    ok = false
                    break
                end
            end
            if ok then
                return recipe
            end
        end
    end
end

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local container = item:getContainer()
    if not container then
        player:sendCancelMessage("You need to use this on a container.")
        return true
    end

    local ids = {}
    for i = 0, container:getSize() - 1 do
        local ingredient = container:getItem(i)
        if ingredient then
            ids[#ids + 1] = ingredient.itemid
        end
    end

    if #ids == 0 then
        return true
    end

    local recipe = matchRecipe(ids)
    if not recipe then
        player:sendCancelMessage("Those ingredients do not form a known potion.")
        return true
    end

    -- remove ingredients
    for i = container:getSize() - 1, 0, -1 do
        local ingredient = container:getItem(i)
        if ingredient then
            ingredient:remove()
        end
    end

    container:addItem(recipe.result, 1)
    player:sendTextMessage(MESSAGE_EVENT_ADVANCE, recipe.message or "You mix the ingredients.")
    return true
end

