local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_EARTHDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_STONES)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_SMALLEARTH)
combat:setArea(createCombatArea(AREA_CROSS1X1))

function onGetFormulaValues(player, level, magicLevel)
    local min = (level / 5) + (magicLevel * 1.8) + 12
    local max = (level / 5) + (magicLevel * 2.8) + 20
    return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("attack")
spell:id(189)
spell:name("Stone Spikes")
spell:words("exori tera mas")
spell:level(32)
spell:mana(45)
spell:isSelfTarget(true)
spell:cooldown(4000)
spell:groupCooldown(2000)
spell:vocation("druid;true", "elder druid;true", "sorcerer;true", "master sorcerer;true")
spell:register()
