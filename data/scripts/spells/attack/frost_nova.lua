local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_ICEDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_ICETORNADO)
combat:setArea(createCombatArea(AREA_CIRCLE3X3))

function onGetFormulaValues(player, level, magicLevel)
    local min = (level / 5) + (magicLevel * 2.2) + 20
    local max = (level / 5) + (magicLevel * 3.2) + 30
    return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("attack")
spell:id(187)
spell:name("Frost Nova")
spell:words("exevo frigo mas")
spell:level(30)
spell:mana(80)
spell:isSelfTarget(true)
spell:cooldown(6000)
spell:groupCooldown(2000)
spell:vocation("druid;true", "elder druid;true", "sorcerer;true", "master sorcerer;true")
spell:register()
