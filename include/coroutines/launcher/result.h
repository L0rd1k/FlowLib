#pragma once

namespace ccflow {

template <class T>
class Result {
public:
    Result() noexcept = default;
    Result(const Result& result) = delete;
    Result(Result&& result) = default;

};

}  // namespace ccflow