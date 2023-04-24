#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace ccflow {

template <class Type>
class ThreadSafeQueue {
public:
    void push_back(Type elem) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push(elem);
        cond_var_.notify_one();
    }

    void emplace(Type&& elem) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.emplace(std::forward<Type>(elem));
        cond_var_.notify_one();
    }

    Type pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        cond_var_.wait(lock, [this]() { return !queue_.empty(); });
        Type elem = queue_.front();
        queue_.pop();
        return elem;
    }

    std::queue<Type>* get_unsafe() const {
        return &queue_;
    }

    std::queue<Type>* get_unsafe() {
        return &queue_;
    }

private:
    std::queue<Type> queue_;
    std::mutex mtx_;
    std::condition_variable cond_var_;
};

}  // namespace ccflow