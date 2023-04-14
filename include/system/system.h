#pragma once

#include <sys/stat.h>
#include <glob.h>

#include <cassert>
#include <string>
#include <vector>

static void makeDir(const std::string& str) {
    const int err = mkdir(str.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    assert("Error creating directory(already exist)" && err != -1);
}

static bool pathExist(const std::string& str) {
    struct stat buffer;
    return (stat(str.c_str(), &buffer) == 0);
}

static void getFolderFiles(std::vector<std::string>& vec ,const std::string& str) {
    glob_t results;
    glob(str.c_str(), GLOB_TILDE, NULL, &results);
    for (unsigned int i = 0; i < results.gl_pathc; i++) {
        vec.push_back(std::string(results.gl_pathv[i]));
    }
    globfree(&results);
}

static uint64_t getFileSize(std::string& name) {
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : 0;
}