#pragma once

#include <functional>
#include <mutex>
#include <memory>

namespace ccflow {

template <class... SlotArgs>
class Slot final {
public:
    template <class SlotClass>
    Slot(SlotClass* slotInst, void (SlotClass::*slotCall)(SlotArgs...))
        : mtx_(new std::mutex()) {
        callback_ = [this, slotInst, slotCall](SlotArgs&&... args) {
            return (slotInst->*slotCall)(std::forward<SlotArgs>(args)...);
        };
    }

    virtual ~Slot() {
        delete mtx_;
    }

    void run(SlotArgs&&... args) {
        std::lock_guard<std::mutex> lock(*mtx_);
        callback_(std::forward<SlotArgs>(args)...);
    }

private:
    std::function<void(SlotArgs...)> callback_;
    std::mutex* mtx_;
};

}  // namespace ccflow
