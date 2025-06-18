#pragma once

class Creature; // Forward declaration

class BehaviorTree
{
public:
	bool tick(Creature* creature);
};
