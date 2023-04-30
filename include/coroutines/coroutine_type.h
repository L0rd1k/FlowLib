#pragma once

#include <coroutine>

#include "definitions/definitions.h"
#include "include/coroutines/promises/promise.h"

namespace ccflow {

namespace coro {

template <class ReturnType = void>
class PromiseType;

template <class ReturnType>
class CCFLOW_API CoroType {
public:
    CoroType() noexcept = default;
    explicit CoroType(std::coroutine_handle<PromiseType<ReturnType>> handle)
        : handle_(handle) {
    }
    CoroType(const CoroType&) noexcept = delete;
    CoroType(CoroType&& ctype) noexcept
        : handle_(std::exchange(ctype.handle_, nullptr)) {}
    ~CoroType() {
        if (handle_ != nullptr)
            handle_.destroy();
    }

    CoroType& operator=(const CoroType&) = delete;
    CoroType& operator=(CoroType&& ctype) noexcept {
        if (std::addressof(ctype) != this) {
            if (handle_ != nullptr) {
                handle_.destroy();
            }
            handle_ = std::exchange(ctype.handle_, nullptr);
        }
    }

public:
    bool is_ready() const noexcept {
        return handle_ == nullptr || handle_.done();
    }

    bool resume() {
        if (!handle_.done)
            handle_.resume();
        return !handle_.done();
    }

    bool destroy() {
        if (handle_ != nullptr) {
            handle_.destroy();
            handle_ = nullptr;
            return true;
        }
        return false;
    }

    /** @brief Suspend execution until resumed.
     *  @details Takes Awaitable object as an argument. **/
    auto operator co_await() const& noexcept {
        class CoAwaitableType : public CoAwaitableTypeBase {
        public:
            auto await_resume() {
                if constexpr (std::is_same_v<void, ReturnType>) {
                    this->handle_.promise().result();
                    return;
                } else {
                    return this->handle_.promise().result();
                }
            }
        };
        return CoAwaitableType{handle_};
    }

    auto operator co_await() const&& noexcept {
        class CoAwaitableType : public CoAwaitableTypeBase {
        public:
            auto await_resume() {
                if constexpr (std::is_same_v<void, ReturnType>) {
                    this->handle_.promise().result();
                    return;
                } else {
                    return std::move(this->handle_.promise()).result();
                }
            }
        };
        return CoAwaitableType{handle_};
    }

    PromiseType<ReturnType>& promise() & {
        return handle_.promise();
    }

    const PromiseType<ReturnType>& promise() const& {
        return handle_.promise();
    }

    PromiseType<ReturnType>&& promise() && {
        return std::move(handle_.promise());
    }

    std::coroutine_handle<PromiseType<ReturnType>> getHandle() {
        return handle_;
    }

public:
    class CoAwaitableTypeBase {
    public:
        CoAwaitableTypeBase(std::coroutine_handle<PromiseType<ReturnType>> handle) noexcept
            : handle_(handle) {
        }

        bool await_ready() const noexcept {
            return !handle_ || handle_.done;
        }

        std::coroutine_handle<> await_suspend(std::coroutine_handle<> await_handle) noexcept {
            handle_.promise().set_handler(await_handle);
            return handle_;
        }

    private:
        std::coroutine_handle<PromiseType<ReturnType>> handle_;
    };

private:
    std::coroutine_handle<ReturnType> handle_{nullptr};
};

}  // namespace coro

}  // namespace ccflow