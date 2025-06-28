local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_BLUE)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

local condition = Condition(CONDITION_REGENERATION)
condition:setParameter(CONDITION_PARAM_TICKS, 20 * 1000)
condition:setParameter(CONDITION_PARAM_MANAGAIN, 40)
condition:setParameter(CONDITION_PARAM_MANATICKS, 4000)
condition:setParameter(CONDITION_PARAM_BUFF_SPELL, true)
combat:addCondition(condition)

local spell = Spell(SPELL_INSTANT)

function spell.onCastSpell(creature, variant)
    return combat:execute(creature, variant)
end

spell:group("healing")
spell:id(316)
spell:name("Mana Flourish")
spell:words("utura mana")
spell:level(20)
spell:mana(50)
spell:isAggressive(false)
spell:isSelfTarget(true)
spell:cooldown(1000)
spell:groupCooldown(1000)
spell:vocation("sorcerer;true", "master sorcerer;true", "druid;true", "elder druid;true", "paladin;true", "royal paladin;true")
spell:register()
