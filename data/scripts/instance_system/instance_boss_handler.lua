-- instance_boss_handler.lua
function onBossDefeated(player, instance)
    local config = InstanceConfig[instance]
    Game.broadcastMessage("The boss " .. config.boss .. " has been defeated in " .. instance .. "!")
    closeInstance(instance)
end

function closeInstance(instance)
    -- Clean up logic
    print("Closing instance:", instance)
end
