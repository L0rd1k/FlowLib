#include <iostream>
#include <string>

#ifdef USE_COROUTINES
#include "include/coroutines/core/coro_core.h"
#endif

#include "include/callbacks/callback.h"

void test1() {
#ifdef USE_COROUTINES
    ccflow::Core core;
    auto result = core.getThreadLauncher()->submit([] {
        std::cout << "hello world" << std::endl;
    });
#endif
}

struct MyVal {};

class Handler {
public:
    Handler() = default;
    void onSignalReceive() {
    }
    void onSlotReceive() {
        std::cout << "DONE";
    }
};


void test2() {
    Handler *obj = new Handler();
    connect(obj, obj, &Handler::onSlotReceive);
    delete obj;
}

int main() {
    test2();
    return 0;
}