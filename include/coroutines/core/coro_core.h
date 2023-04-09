#pragma once

#include <memory>

#include "definitions/definitions.h"
#include "include/coroutines/thread/thread_launcher.h"

namespace ccflow {

class CCFLOW_API Core {
public:
    Core();
    virtual ~Core() noexcept;
    Core(const Core& core);
    std::shared_ptr<ThreadLauncher> getThreadLauncher() const noexcept;

private:
    std::shared_ptr<ThreadLauncher> threadLauncher_;
};

}  // namespace ccflow