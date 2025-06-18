#include "behaviortree.h"
#include "creature.h"
#include "tools.h"

void SequenceNode::addChild(std::unique_ptr<BehaviorNode> child) {
    children.emplace_back(std::move(child));
}

bool SequenceNode::tick(Creature* creature, Blackboard& board) {
    for (auto& child : children) {
        if (!child->tick(creature, board)) {
            return false;
        }
    }
    return true;
}

void SelectorNode::addChild(std::unique_ptr<BehaviorNode> child) {
    children.emplace_back(std::move(child));
}

bool SelectorNode::tick(Creature* creature, Blackboard& board) {
    for (auto& child : children) {
        if (child->tick(creature, board)) {
            return true;
        }
    }
    return false;
}

ConditionNode::ConditionNode(std::function<bool(Creature*)> cond) : condition(std::move(cond)) {}

bool ConditionNode::tick(Creature* creature, Blackboard&) {
    return condition(creature);
}

ActionNode::ActionNode(std::function<bool(Creature*)> action) : action(std::move(action)) {}

bool ActionNode::tick(Creature* creature, Blackboard&) {
    return action(creature);
}

BehaviorTree::BehaviorTree(std::unique_ptr<BehaviorNode> root) : root(std::move(root)) {}

bool BehaviorTree::tick(Creature* creature) {
    if (!root) {
        return false;
    }
    return root->tick(creature, board);
}

bool CooldownNode::tick(Creature*, Blackboard& board) {
    uint64_t now = OTSYS_TIME();
    auto it = board.timestamps.find(key);
    if (it == board.timestamps.end() || now >= it->second) {
        board.timestamps[key] = now + delay;
        return true;
    }
    return false;
}

