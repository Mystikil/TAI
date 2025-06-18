-- instance_auto_register.lua
local files = {
    "instance_config.lua",
    "instance_chunk_spawner.lua",
    "instance_boss_handler.lua",
    "instance_teleport_trigger.lua",
    "instance_chunk_logic.lua"
}

for _, file in ipairs(files) do
    dofile("data/scripts/instance_system/" .. file)
end
