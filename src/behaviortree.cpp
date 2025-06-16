#include "behaviortree.h"
#include "creature.h"

void SequenceNode::addChild(std::unique_ptr<BehaviorNode> child) {
    children.emplace_back(std::move(child));
}

bool SequenceNode::tick(Creature* creature) {
    for (auto& child : children) {
        if (!child->tick(creature)) {
            return false;
        }
    }
    return true;
}

void SelectorNode::addChild(std::unique_ptr<BehaviorNode> child) {
    children.emplace_back(std::move(child));
}

bool SelectorNode::tick(Creature* creature) {
    for (auto& child : children) {
        if (child->tick(creature)) {
            return true;
        }
    }
    return false;
}

ConditionNode::ConditionNode(std::function<bool(Creature*)> cond) : condition(std::move(cond)) {}

bool ConditionNode::tick(Creature* creature) {
    return condition(creature);
}

ActionNode::ActionNode(std::function<bool(Creature*)> action) : action(std::move(action)) {}

bool ActionNode::tick(Creature* creature) {
    return action(creature);
}

BehaviorTree::BehaviorTree(std::unique_ptr<BehaviorNode> root) : root(std::move(root)) {}

bool BehaviorTree::tick(Creature* creature) {
    if (!root) {
        return false;
    }
    return root->tick(creature);
}
