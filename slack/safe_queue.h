// Based on https://github.com/juanchopanza/cppblog/tree/master/Concurrency/queue
//
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std::literals;

namespace slack
{

template<typename T>
class safe_queue
{
public:
    bool empty()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        return queue_.empty();
    }

    bool count()
    {}

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while(queue_.empty())
        {
            cond_.wait(mlock);
        }
        auto val = queue_.front();
        queue_.pop();
        return val;
    }

    bool pop(T &item, std::chrono::milliseconds timeout=500ms)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while(queue_.empty())
        {
            if(cond_.wait_for(mlock, timeout) == std::cv_status::timeout) return false;
        }
        item = queue_.front();
        queue_.pop();
        return true;
    }

    void push(const T &item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }

    safe_queue() = default;
    safe_queue(const safe_queue &) = delete;            // disable copying
    safe_queue &operator=(const safe_queue &) = delete; // disable assignment

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

} //namespace slack