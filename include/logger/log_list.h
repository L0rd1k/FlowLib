#pragma once

#include <inttypes.h>

#include <string>

#include "include/system/system.h"

namespace ccflow {

namespace Watch {

struct LogInfo {
public:
    LogInfo(std::string_view name, uint32_t size = 0) : name(name), size(size) {}
    std::string name;
    uint32_t size;
};

class LogList {
public:
    LogList(uint32_t fileSize, uint32_t folderSize)
        : limitFileSize_(fileSize),
          limitFolderSize_(folderSize){};

protected:
    bool init(std::string path) {
        if (!pathExist(path)) {
            makeDir(path);
        }
        getFiles(entries, path + "/*");
        for (auto& elem : entries) {
            elem.size = getFileSize(elem.name);
            totalFolderSize_ += elem.size;
        }
        return true;
    }

    void getFiles(std::vector<LogInfo>& vec, const std::string& str) {
        glob_t results;
        glob(str.c_str(), GLOB_TILDE, NULL, &results);
        for (unsigned int i = 0; i < results.gl_pathc; i++) {
            vec.push_back(LogInfo(std::string(results.gl_pathv[i])));
        }
        globfree(&results);
    }

protected:
    uint32_t limitFileSize_;
    uint32_t limitFolderSize_;

    // uint32_t totalFileSize_;
    uint32_t totalFolderSize_;
    std::vector<LogInfo> entries;
};

}  // namespace Watch

}  // namespace ccflow
