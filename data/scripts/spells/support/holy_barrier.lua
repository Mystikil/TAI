local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_HOLYDAMAGE)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

local condition = Condition(CONDITION_ATTRIBUTES)
condition:setParameter(CONDITION_PARAM_TICKS, 45 * 1000)
condition:setParameter(CONDITION_PARAM_SKILL_SHIELDPERCENT, 120)
condition:setParameter(CONDITION_PARAM_BUFF_SPELL, true)
combat:addCondition(condition)

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("support")
spell:id(192)
spell:name("Holy Barrier")
spell:words("utamo sancta")
spell:level(24)
spell:mana(80)
spell:isAggressive(false)
spell:isSelfTarget(true)
spell:cooldown(2000)
spell:groupCooldown(2000)
spell:vocation("paladin;true", "royal paladin;true", "knight;true", "elite knight;true")
spell:register()
