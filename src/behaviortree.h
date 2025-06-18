#ifndef FS_BEHAVIORTREE_H
#define FS_BEHAVIORTREE_H

#include <functional>
#include <memory>
#include <vector>

class Creature;

class BehaviorNode {
public:
    virtual ~BehaviorNode() = default;
    virtual bool tick(Creature* creature) = 0;
};

class SequenceNode : public BehaviorNode {
public:
    void addChild(std::unique_ptr<BehaviorNode> child);
    bool tick(Creature* creature) override;
private:
    std::vector<std::unique_ptr<BehaviorNode>> children;
};

class SelectorNode : public BehaviorNode {
public:
    void addChild(std::unique_ptr<BehaviorNode> child);
    bool tick(Creature* creature) override;
private:
    std::vector<std::unique_ptr<BehaviorNode>> children;
};

class ConditionNode : public BehaviorNode {
public:
    explicit ConditionNode(std::function<bool(Creature*)> cond);
    bool tick(Creature* creature) override;
private:
    std::function<bool(Creature*)> condition;
};

class ActionNode : public BehaviorNode {
public:
    explicit ActionNode(std::function<bool(Creature*)> action);
    bool tick(Creature* creature) override;
private:
    std::function<bool(Creature*)> action;
};

class BehaviorTree {
public:
    explicit BehaviorTree(std::unique_ptr<BehaviorNode> root);
    bool tick(Creature* creature);
private:
    std::unique_ptr<BehaviorNode> root;
};

#endif // FS_BEHAVIORTREE_H
