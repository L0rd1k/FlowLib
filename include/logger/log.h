#pragma once

#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>

#include "include/date_time.h"
#include "log_writer.h"

namespace ccflow {

namespace Watch {

class Log : public LogWriter {
public:
    static Log& inst() {
        static Log obj;
        return obj;
    }

    template <class... Args>
    void print(std::string_view type, Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx_);
        std::stringstream str;
        str << "[" << getTime() << "]";
        (void)(int[]){0, (void(str << " " << std::forward<Args>(args)), 0)...};
        str << std::endl;
        write(str.str());
        std::cout << "[" << type << "]" << str.str();
    }

private:
    std::mutex mtx_;
};

template <class... Args>
void error(Args&&... args) {
    std::string type = "\033[1;31;49mError\033[0m";
    Log::inst().print(type, args...);
}

template <class... Args>
void warning(Args&&... args) {
    std::string type = "\033[1;35;49mWarning\033[0m";
    Log::inst().print(type, args...);
}

template <class... Args>
void trace(Args&&... args) {
    std::string type = "\033[1;32;49mTrace\033[0m";
    Log::inst().print(type, args...);
}

template <class... Args>
void info(Args&&... args) {
    std::string type = "\033[1;34;49mInfo\033[0m";
    Log::inst().print(type, args...);
}

}  // namespace Watch

}  // namespace ccflow
