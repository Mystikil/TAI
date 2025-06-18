// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_SCHEDULER_H
#define FS_SCHEDULER_H

#include "tasks.h"
#include "thread_holder_base.h"
#include <memory>

static constexpr int32_t SCHEDULER_MINTICKS = 50;

// A small task that will be executed later.
// Using unique_ptr keeps us from forgetting to delete it.
class SchedulerTask : public Task
{
public:
	void setEventId(uint32_t id) { eventId = id; }
	uint32_t getEventId() const { return eventId; }

	uint32_t getDelay() const { return delay; }

private:
        SchedulerTask(uint32_t delay, TaskFunc&& f) : Task(std::move(f)), delay(delay) {}

	uint32_t eventId = 0;
	uint32_t delay = 0;

        friend std::unique_ptr<SchedulerTask> createSchedulerTask(uint32_t, TaskFunc&&);
};

using SchedulerTaskPtr = std::unique_ptr<SchedulerTask>;

// Create a task that the scheduler can run.
SchedulerTaskPtr createSchedulerTask(uint32_t delay, TaskFunc&& f);

class Scheduler : public ThreadHolder<Scheduler>
{
public:
        // Add a task and get back its id so we can stop it later.
        uint32_t addEvent(SchedulerTaskPtr task);
        void stopEvent(uint32_t eventId);

	void shutdown();

	void threadMain() { io_context.run(); }

private:
	std::atomic<uint32_t> lastEventId{0};
	std::unordered_map<uint32_t, boost::asio::steady_timer> eventIdTimerMap;
	boost::asio::io_context io_context;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work{io_context.get_executor()};
};

extern Scheduler g_scheduler;

#endif // FS_SCHEDULER_H
