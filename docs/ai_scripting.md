# AI Scripting

This server allows customizing monster and NPC behavior through Lua scripts. In addition to the traditional callbacks such as `onThink`, `onCreatureSay` and `onCreatureAppear`, a lightweight behavior tree system is available to compose more advanced logic in C++.

## Behavior Trees

Behavior trees are composed of nodes evaluated each server tick. The basic node types provided are:

- **Sequence** – runs children in order until one fails.
- **Selector** – runs children in order until one succeeds.
- **Condition** – executes a predicate and succeeds or fails.
- **Action** – performs work and returns success or failure.

C++ code can build trees and attach them to a monster or NPC instance using `setBehaviorTree()`.

```cpp
auto root = std::make_unique<SequenceNode>();
root->addChild(std::make_unique<ConditionNode>([](Creature* self) {
    return self->getHealth() < self->getMaxHealth() / 2;
}));
root->addChild(std::make_unique<ActionNode>([](Creature* self) {
    // placeholder flee logic
    self->setFollowCreature(nullptr);
    return true;
}));
monster->setBehaviorTree(std::make_unique<BehaviorTree>(std::move(root)));
```

This example causes the monster to stop following its target when below half health. Behavior trees run in `onThink` before script callbacks.

Use trees sparingly—heavy logic can still impact performance.

