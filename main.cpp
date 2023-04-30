#include <unistd.h>

#include <iostream>
#include <string>

#include "include/callbacks/callback.h"
#include "include/callbacks/callback_handler.h"
#include "include/callbacks/signal.h"
#include "include/utils/date_time.h"
#include "include/logger/log.h"
#include "include/utils/timer.h"

#include "include/structs/thread_safe_queue.h"

#include "include/coroutines/promises/promise.h"
#include "include/coroutines/coroutine_type.h"

int main() {
    ccflow::Timer _tm;
    ccflow::Watch::error("Check this line");
    std::cout << _tm.passedMs() << std::endl;

    ccflow::ThreadSafeQueue<int> queue_;
    std::cout << queue_.get_unsafe()->size() << std::endl;
    // ccflow::Watch::warning("Check this line");
    // ccflow::Watch::trace("Check this line");
    // ccflow::Watch::info("Check this line");



    return 0;
}