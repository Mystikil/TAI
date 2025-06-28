local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_GREEN)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

local condition = Condition(CONDITION_HASTE)
condition:setParameter(CONDITION_PARAM_TICKS, 15000)
condition:setFormula(0.6, -48, 0.6, -48)
combat:addCondition(condition)

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("support")
spell:id(315)
spell:name("Speed Boost")
spell:words("utani tempo lux")
spell:level(20)
spell:mana(80)
spell:isAggressive(false)
spell:isSelfTarget(true)
spell:cooldown(2000)
spell:groupCooldown(2000)
spell:vocation("sorcerer;true", "druid;true", "paladin;true", "knight;true", "master sorcerer;true", "elder druid;true", "royal paladin;true", "elite knight;true")
spell:register()
