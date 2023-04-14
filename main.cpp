#include <unistd.h>

#include <iostream>
#include <string>

#ifdef USE_COROUTINES
#include "include/coroutines/core/coro_core.h"
#endif

#include "include/callbacks/callback.h"
#include "include/callbacks/callback_handler.h"
#include "include/callbacks/signal.h"
#include "include/date_time.h"
#include "include/logger/log.h"
#include "include/timer.h"

void test1() {
#ifdef USE_COROUTINES
    ccflow::Core core;
    auto result = core.getThreadLauncher()->submit([] {
        std::cout << "hello world" << std::endl;
    });
#endif
}

int main() {
    ccflow::Timer _tm;
    ccflow::Watch::error("Check this line");
    std::cout << _tm.passedMs() << std::endl;

    // ccflow::Watch::warning("Check this line");
    // ccflow::Watch::trace("Check this line");
    // ccflow::Watch::info("Check this line");

    return 0;
}