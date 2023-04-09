#pragma once

#include "callback_handler.h"

namespace ccflow {

template <class ReturnType, class SlotType, class... Args>
class CallbackList final {
public:
    static CallbackList<ReturnType, SlotType, Args...>& inst() {
        static CallbackList<ReturnType, SlotType, Args...> obj;
        return obj;
    }
private:
    std::vector<std::unique_ptr<CallbackHandlerBase> > _callbacks;
};

}  // namespace ccflow