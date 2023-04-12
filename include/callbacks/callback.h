#pragma once

template <class SignalClass, class SlotClass, class... SlotArgs>
static void connect(SignalClass *signalInst, SlotClass *slotInst, void (SlotClass::*slot)(SlotArgs...)) {
    signalInst->addCallback(slotInst, slot);
}


