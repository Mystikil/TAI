local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_DEATHDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MORTAREA)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_DEATH)

function onGetFormulaValues(player, level, magicLevel)
    local min = (level / 5) + (magicLevel * 1.6) + 10
    local max = (level / 5) + (magicLevel * 2.5) + 18
    return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("attack")
spell:id(188)
spell:name("Shadow Bolt")
spell:words("exori mort hur")
spell:level(24)
spell:mana(40)
spell:range(3)
spell:needCasterTargetOrDirection(true)
spell:blockWalls(true)
spell:cooldown(3000)
spell:groupCooldown(2000)
spell:vocation("sorcerer;true", "master sorcerer;true")
spell:register()
