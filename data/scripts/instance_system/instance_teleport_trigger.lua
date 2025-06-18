-- instance_teleport_trigger.lua
local function onStepIn(creature, item, position, fromPosition)
    if not creature:isPlayer() then return true end
    local instanceName = item:getAttribute("instance_name") or "dungeon_1"
    spawnInstanceChunk(instanceName)
    creature:teleportTo(Position(1000, 1000, 7)) -- Replace with instance entry
    return true
end

function onAddTileItem(moveItem, tileItem, position)
    if tileItem:getActionId() == 50000 then
        onStepIn(moveItem:getTopCreature(), tileItem, position, position)
    end
end
