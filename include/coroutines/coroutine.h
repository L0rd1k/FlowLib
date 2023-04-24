#pragma once

#include <coroutine>

#include "definitions/definitions.h"

namespace ccflow {

template <class ReturnType>
class CCFLOW_API CoroutineType {
public:
    using chandle = std::coroutine_handle<promise_type>;

public:
    CoroutineType() noexcept = default;
    CoroutineType(const CoroutineType&) = delete;
    CoroutineType(chandle handle) : coroutine_(handle) {}

    ~CoroutineType() {
        if (corou1tine_)
            coroutine_.destroy();
    }

private:
    chandle coroutine_{nullptr};
};

};  // namespace ccflow