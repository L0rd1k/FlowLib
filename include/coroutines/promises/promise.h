#pragma once

#include <coroutine>
#include <exception>

#include "definitions/definitions.h"
#include "include/coroutines/coroutine_type.h"
#include "include/coroutines/promises/promise_base.h"
namespace ccflow {

namespace coro {

template <class ReturnType = void>
class CoroType;

/** @brief Submitting the result of coroutines. */
template <class ReturnType>
class PromiseType : public PromiseBase {
public:
    PromiseType() noexcept = default;
    ~PromiseType() = default;

    inline CoroType<ReturnType> get_return_object() noexcept {
        return CoroType<ReturnType>{std::coroutine_handle<PromiseType<ReturnType>>::from_promise(*this)};
    }

    void return_value(ReturnType ret_val) {
        ret_val_ = std::move(ret_val);
    }

    ReturnType&& get_result() && {
        if (exception_) {
            std::rethrow_exception(exception_);
        }
        return std::move(ret_val_);
    }

    const ReturnType& get_result() const& {
        if (exception_) {
            std::rethrow_exception(exception_);
        }
        return ret_val_;
    }

private:
    ReturnType ret_val_;
};

// ########################################################################

template <>
class PromiseType<void> : public PromiseBase {
public:
    PromiseType() noexcept = default;
    ~PromiseType() = default;

    inline CoroType<void> get_return_object() noexcept {
        return CoroType<>{std::coroutine_handle<PromiseType<void>>::from_promise(*this)};
    }

    void return_void() noexcept {}

    void get_result() {
        if (exception_) {
            std::rethrow_exception(exception_);
        }
    }

};

}  // namespace coro

}  // namespace ccflow
