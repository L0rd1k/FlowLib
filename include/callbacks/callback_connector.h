#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "slot.h"


namespace ccflow {

class CallbackConnector {
public:
    static CallbackConnector &inst() {
        std::lock_guard<std::mutex> lock(mtx_);
        static CallbackConnector inst;
        return inst;
    }

    template <class ReturnType, class SignalClass, class... SignalArgs, class SlotClass, class... SlotArgs>
    void addConnection(SignalClass *signalInst,
                       ReturnType (SignalClass::*signalCall)(SignalArgs...),
                       SlotClass *slotInst,
                       ReturnType (SlotClass::*slotCall)(SlotArgs...)) {
        std::lock_guard<std::mutex> lock(mtx_);


    }

private:
    static std::mutex mtx_;
};

std::mutex CallbackConnector::mtx_;

}  // namespace ccflow