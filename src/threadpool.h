#pragma once

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Threadpool {
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mut;
    std::condition_variable cv;
    bool running = true;

public:
    Threadpool(size_t n = std::thread::hardware_concurrency());
    ~Threadpool();

    void enqueue(std::function<void()> task);
};

#endif