#pragma once

#include <coroutine>
#include <exception>

#include "definitions/definitions.h"
namespace ccflow {

namespace coro {

class CCFLOW_API PromiseBase {
public:
    friend class AwaitableType;
    class CCFLOW_API AwaitableType {
        constexpr bool await_ready() const noexcept { return false; }
        constexpr void await_resume() const noexcept {}

        template <class PromiseType>
        constexpr std::coroutine_handle<> await_suspend(std::coroutine_handle<PromiseType> cr) const noexcept {
            auto& promise = cr.promise();
            if (promise.chandle_ != nullptr)
                return promise.chandle_;
            else
                return std::noop_coroutine();
        }
    };

    PromiseBase() noexcept = default;
    ~PromiseBase() = default;

    auto initial_suspend() {
        return std::suspend_always{};
    }

    auto final_suspend() {
        return AwaitableType{};
    }

    void unhandled_exception() {
        exception_ = std::current_exception();
    }

    void set_handler(std::coroutine_handle<> chandle) noexcept {
        chandle_ = chandle;
    }

protected:
    std::coroutine_handle<> chandle_{nullptr};
    std::exception_ptr exception_{};
};

}  // namespace coro

}  // namespace ccflow