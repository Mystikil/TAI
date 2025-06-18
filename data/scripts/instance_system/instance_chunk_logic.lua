-- instance_chunk_logic.lua
function spawnRareMinerals(area, list)
    for _, mineral in ipairs(list) do
        local pos = Position(area.x + math.random(0, area.w), area.y + math.random(0, area.h), area.z)
        Game.createItem(mineral, 1, pos)
    end
end
