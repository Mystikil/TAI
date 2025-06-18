-- instance_dungeon.lua
local InstanceManager = {
    instances = {},
    activeSpawns = {},
    bossDefeated = {}
}

function InstanceManager:startInstance(player, dungeonId)
    local instanceId = player:getGuid() .. "_" .. os.time()
    local difficulty = self:calculateDifficulty(player)
    self.instances[instanceId] = {
        dungeonId = dungeonId,
        difficulty = difficulty,
        created = os.time(),
        players = { player:getGuid() }
    }
    self:spawnMonsters(instanceId)
    player:teleportTo(self:getEntrancePosition(dungeonId))
end

function InstanceManager:calculateDifficulty(player)
    local level = player:getLevel()
    local chance = math.random(100)
    local base = math.ceil(level / 10)
    if chance > 80 then
        return base + 2
    elseif chance > 50 then
        return base + 1
    end
    return base
end

function InstanceManager:spawnMonsters(instanceId)
    local dungeon = self.instances[instanceId]
    local pos = Position(1000, 1000, 7) -- Example
    local monsterName = "Orc"
    local monster = Game.createMonster(monsterName, pos)
    monster:setCustomAttribute("instanceId", instanceId)
end

function InstanceManager:getEntrancePosition(dungeonId)
    return Position(1000, 1000, 7) -- Replace with dynamic
end

function onTileEnter(creature, item, position, fromPosition)
    if creature:isPlayer() then
        InstanceManager:startInstance(creature, 1)
    end
end
