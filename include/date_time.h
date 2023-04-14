#pragma once

#include <chrono>
#include <ctime>
#include <iostream>

static std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t end = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&end);
}

static std::string getTime() {
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::string(std::ctime(&time), 11, 8);
}