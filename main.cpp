#include <iostream>
#include <string>

#ifdef USE_COROUTINES
#include "include/coroutines/core/coro_core.h"
#endif

#include "include/callbacks/callback.h"
#include "include/callbacks/signal.h"
#include "include/callbacks/callback_handler.h"
void test1() {
#ifdef USE_COROUTINES
    ccflow::Core core;
    auto result = core.getThreadLauncher()->submit([] {
        std::cout << "hello world" << std::endl;
    });
#endif
}



int main() {
    return 0;
}