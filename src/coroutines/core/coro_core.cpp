#include "include/coroutines/core/coro_core.h"

ccflow::Core::Core() {
}

ccflow::Core::~Core() noexcept {
}

ccflow::Core::Core(const ccflow::Core& core) {
    threadLauncher_ = std::make_shared<ccflow::ThreadLauncher>();
}

std::shared_ptr<ccflow::ThreadLauncher> ccflow::Core::getThreadLauncher() const noexcept {
    return threadLauncher_;
}
