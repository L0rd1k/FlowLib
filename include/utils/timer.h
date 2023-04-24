#pragma once

#include <chrono>

namespace ccflow {

class Timer {
private:
    using clk = std::chrono::steady_clock;
    using sec = std::chrono::duration<double, std::ratio<1>>;

public:
    Timer() { start(); }
    void start() { start_ = clk::now(); }
    const double passed() { return std::chrono::duration_cast<sec>(clk::now() - start_).count(); }
    const double passedMs() { return passed() * 1000; }
    const bool elapsed(int32_t ms) { return passedMs() > ms; }
private:
    std::chrono::time_point<clk> start_;
};

}  // namespace ccflow