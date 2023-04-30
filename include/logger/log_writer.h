#pragma once

#include <fstream>
#include <iostream>
#include <string_view>

#include "include/utils/date_time.h"
#include "include/logger/log_list.h"

namespace ccflow {

namespace Watch {

class LogWriter : public LogList {
public:
    LogWriter() : LogList(1000000, 100000000) {
        init("logs");
        openFile("logs/" + getCurrentDateTime());
    }
    virtual ~LogWriter() {
        closeFile();
    }

    bool openFile(std::string str) {
        file_.open(str, std::ios::in | std::ios::app);
        if (!file_.is_open())
            return false;

        entries.push_back(LogInfo(str));    
        return true;
    }

    bool write(std::string_view str) {
        if (entries.back().size >= limitFileSize_) {
            pushFile();
        }
        if (totalFolderSize_ >= limitFolderSize_) {
            popFile();
        }
        file_ << str;
        entries.back().size += str.size();
        totalFolderSize_ += str.size();
        return true;
    }

    void pushFile() {
        file_.close();
        if (!file_.is_open()) {
            openFile("logs/" + getCurrentDateTime());
        }
    }

    void popFile() {
        auto first = entries.front();
        totalFolderSize_ -= first.size;
        remove(first.name.c_str());
        entries.erase(entries.begin());
    }

    bool closeFile() {
        if(file_.is_open()) {
            file_.close();
            return true;
        }
        return false;
    }

private:
    std::ofstream file_;
};

}  // namespace Watch

}  // namespace ccflow
