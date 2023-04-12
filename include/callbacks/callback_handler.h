#pragma once

#include <iostream>
#include <vector>
#include <mutex>

#include "slot.h"

namespace ccflow {

template <class ReturnType, class... SlotArgs>
class CallbackHandler {
public:
    CallbackHandler() = default;
    virtual ~CallbackHandler() = default;

    template <class SlotClass>
    void addCallback(SlotClass* slotInst, ReturnType (SlotClass::*slot)(SlotArgs...)) {
        if(slotInst) {
            std::cout << "Add callback" << std::endl;
            std::lock_guard<std::mutex> lock(mtx_);
            slots_.emplace_back(std::make_shared<Slot<SlotArgs...>>(slotInst, slot));
        }
    }

    std::vector<std::shared_ptr<Slot<SlotArgs...>>> getSlots() {
        std::lock_guard<std::mutex> lock(mtx_);
        return slots_;
    }

private:
    std::vector<std::shared_ptr<Slot<SlotArgs...>>> slots_;
    std::mutex mtx_;
};

}  // namespace ccflow