#include "threadpool.h"

using namespace std;

ThreadPool::ThreadPool(size_t threads) {
    for (size_t i= 0; i < threads; i++) {
        workers.emplace_back([this] {
            for (;;) {
                function<void()> task;
                {
                    unique_lock<mutex> lock(queueMutex);
                    condition.wait(lock, [this]{ return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) return;
                    task= move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::enqueue(function<void()> task) {
    {
        unique_lock<mutex> lock(queueMutex);
        tasks.push(move(task));
    }
    condition.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(queueMutex);
        stop= true;
    }
    condition.notify_all();
    for (thread &worker : workers) {
        if (worker.joinable()) worker.join();
    }
}
