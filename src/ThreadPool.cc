//
// Created by boris on 21.12.2021.
//

#include "thread_pool/ThreadPool.h"

ThreadPool::ThreadPool(const std::uint_fast32_t &_thread_count)
        : threadCount(_thread_count ? _thread_count : std::thread::hardware_concurrency()), threads(new std::thread[_thread_count ? _thread_count : std::thread::hardware_concurrency()])
    {
        createThreads();
    }
ThreadPool::~ThreadPool() {
    waitForTasks();
    running = false;
    destroyThreads();
}

std::uint_fast64_t ThreadPool::getTasksQueued() const {
    const std::scoped_lock lock(queueMutex);
    return tasks.size();
}


std::uint_fast32_t ThreadPool::getTasksRunning() const {
    return tasksTotal - (std::uint_fast32_t) getTasksQueued();
}

//template <typename F>
//void ThreadPool::pushTask(const F &task) {
//    tasksTotal++;
//    {
//        const std::scoped_lock lock(queueMutex);
//        tasks.push(std::function<void()>(task));
//    }
//}

//template <typename F, typename... A>
//void ThreadPool::pushTask(const F &task, const A &...args) {
//    pushTask([task, args...] { task(args...); });
//}

void ThreadPool::waitForTasks() {
    while (true) {
        if (!paused) {
            if (tasksTotal == 0) { break; }
        } else {
            if (getTasksRunning() == 0) { break; }
        }
        sleepOrYield();
    }
}

void ThreadPool::createThreads() {
    for (std::uint_fast32_t i = 0; i < threadCount; i++) {
        threads[i] = std::thread(&ThreadPool::worker, this);
    }
}


void ThreadPool::destroyThreads() {
    for (std::uint_fast32_t i = 0; i < threadCount; i++) {
        threads[i].join();
    }
}

bool ThreadPool::popTask(std::function<void()> &task) {
    const std::scoped_lock lock(queueMutex);
    if (tasks.empty()) {
        return false;
    } else {
        task = std::move(tasks.front());
        tasks.pop();
        return true;
    }
}

void ThreadPool::sleepOrYield() {
    if (sleepDuration) {
        std::this_thread::sleep_for(std::chrono::microseconds(sleepDuration));
    } else {
        std::this_thread::yield();
    }
}

void ThreadPool::worker() {
    while (running) {
        std::function<void()> task;
        if (!paused && popTask(task)) {
            task();
            tasksTotal--;
        } else {
            sleepOrYield();
        }
    }
}
