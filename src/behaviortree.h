#ifndef FS_BEHAVIORTREE_H
#define FS_BEHAVIORTREE_H

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>

class Creature;

class BehaviorNode {
public:
    virtual ~BehaviorNode() = default;
    virtual bool tick(Creature* creature, struct Blackboard& board) = 0;
};

class SequenceNode : public BehaviorNode {
public:
    void addChild(std::unique_ptr<BehaviorNode> child);
    bool tick(Creature* creature, Blackboard& board) override;
private:
    std::vector<std::unique_ptr<BehaviorNode>> children;
};

class SelectorNode : public BehaviorNode {
public:
    void addChild(std::unique_ptr<BehaviorNode> child);
    bool tick(Creature* creature, Blackboard& board) override;
private:
    std::vector<std::unique_ptr<BehaviorNode>> children;
};

class ConditionNode : public BehaviorNode {
public:
    explicit ConditionNode(std::function<bool(Creature*)> cond);
    bool tick(Creature* creature, Blackboard& board) override;
private:
    std::function<bool(Creature*)> condition;
};

class ActionNode : public BehaviorNode {
public:
    explicit ActionNode(std::function<bool(Creature*)> action);
    bool tick(Creature* creature, Blackboard& board) override;
private:
    std::function<bool(Creature*)> action;
};

struct Blackboard {
    std::unordered_map<std::string, int> ints;
    std::unordered_map<std::string, std::string> strings;
    std::unordered_map<std::string, uint64_t> timestamps;
};

class BehaviorTree {
public:
    explicit BehaviorTree(std::unique_ptr<BehaviorNode> root);
    bool tick(Creature* creature);
    Blackboard& getBlackboard() { return board; }
private:
    std::unique_ptr<BehaviorNode> root;
    Blackboard board;
};

class CooldownNode : public BehaviorNode {
public:
    CooldownNode(const std::string& key, uint32_t delay) : key(key), delay(delay) {}
    bool tick(Creature* creature, Blackboard& board) override;
private:
    std::string key;
    uint32_t delay;
};

#endif // FS_BEHAVIORTREE_H
