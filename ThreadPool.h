//
// Created by boris on 21.12.2021.
//

#ifndef VNIIRA_THREADPOOL_H
#define VNIIRA_THREADPOOL_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>


class ThreadPool {
public:

    ThreadPool(const std::uint_fast32_t &_thread_count = std::thread::hardware_concurrency());
    virtual ~ThreadPool();

    /**
     * @brief Получить количестиво задач ожидающих выполнение
     *
     * @return Количестиво задач ожидающих выполнение
     */
    std::uint_fast64_t getTasksQueued() const;

    /**
     * @brief Получить количество выполняемых задач в разных потоках
     *
     * @return количество выполняемых задач
     */
    std::uint_fast32_t getTasksRunning() const;

    /**
     * @brief Добавить функцию без аргументов в очередь выполнения
     *
     * @tparam F тип функции
     * @param task задание на выполнение
     */
    template <typename F>
    void pushTask(const F &task);

    /**
     * @brief Добавить функцию в очередь выполнения
     *
     * @tparam F тип функции
     * @tparam A набор типов аргументов
     * @param task задание на выполнение
     * @param args параметры функции
     */
    template <typename F, typename... A>
    void pushTask(const F &task, const A &...args);

    /**
     * @brief Функция для ожидания завершения исполнения
     */
    void waitForTasks();

    /**
     * @brief Переменная для постановки на паузу процесса изсполнения задач из очереди
     */
    std::atomic<bool> paused = false;

    /**
     * @brief Время на которое процесс останавливается если очередь задач пуста, потом идет повторная проверка
     */
    std::uint_fast32_t sleepDuration = 1000;

private:
    void createThreads();
    void destroyThreads();
    bool popTask(std::function<void()> &task);
    void sleepOrYield();
    void worker();

    mutable std::mutex queueMutex = {};
    std::atomic<bool> running = true;
    std::queue<std::function<void()>> tasks = {};
    std::uint_fast32_t threadCount;
    std::unique_ptr<std::thread[]> threads;
    std::atomic<std::uint_fast32_t> tasksTotal = 0;
};


#endif//VNIIRA_THREADPOOL_H
