local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_FIREDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_FIREAREA)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_FIRE)

function onGetFormulaValues(player, level, magicLevel)
    local min = (level / 5) + (magicLevel * 2.0) + 15
    local max = (level / 5) + (magicLevel * 3.4) + 25
    return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("attack")
spell:id(312)
spell:name("Star Fire")
spell:words("exori stellar flam")
spell:level(40)
spell:mana(55)
spell:range(3)
spell:needCasterTargetOrDirection(true)
spell:blockWalls(true)
spell:cooldown(3000)
spell:groupCooldown(2000)
spell:vocation("sorcerer;true", "master sorcerer;true")
spell:register()
