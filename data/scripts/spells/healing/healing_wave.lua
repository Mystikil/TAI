local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_BLUE)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, false)
combat:setArea(createCombatArea(AREA_CIRCLE2X2))

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    local min = (creature:getLevel() / 5) + (creature:getMagicLevel() * 1.5) + 30
    local max = (creature:getLevel() / 5) + (creature:getMagicLevel() * 3.0) + 50
    for _, target in ipairs(combat:getTargets(creature, variant)) do
        local master = target:getMaster()
        if target:isPlayer() or (master and master:isPlayer()) then
            doTargetCombat(creature, target, COMBAT_HEALING, min, max)
        end
    end
    return true
end

spell:group("healing")
spell:id(195)
spell:name("Healing Wave")
spell:words("exura mas sio")
spell:level(34)
spell:mana(120)
spell:isAggressive(false)
spell:cooldown(4000)
spell:groupCooldown(2000)
spell:vocation("druid;true", "elder druid;true")
spell:register()
