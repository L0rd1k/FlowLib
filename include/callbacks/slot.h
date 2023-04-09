#pragma once

#include <functional>

namespace ccflow {

template <class ReturnType, class... SlotArgs>
class Slot {
public:
    template <class SlotClass>
    Slot(SlotClass* slotInst, ReturnType (SlotClass::*slotCall)(SlotArgs...)) {
        callback_ = [this, slotInst, slotCall](SlotArgs&&... args) {
            return (slotInst->*slotCall)(std::forward<SlotArgs>(args)...);
        };
    }

private:
    std::function<ReturnType(SlotArgs...)> callback_;
};

}  // namespace ccflow
