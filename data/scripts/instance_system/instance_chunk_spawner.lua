-- instance_chunk_spawner.lua
function spawnInstanceChunk(instance)
    local chunk = InstanceConfig[instance].chunk
    -- Load map chunk logic (assumes chunks are pre-defined .otbm or template references)
    dofile("data/scripts/instance_chunks/" .. chunk .. ".lua")
end
