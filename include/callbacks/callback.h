#pragma once

#include <utility>

#include "callback_connector.h"
#include "callback_list.h"

template <class ReturnType, class SignalClass, class SlotClass, class... SlotArgs>
static void connect(SignalClass *signalInst, SlotClass *slotInst, ReturnType (SlotClass::*slot)(SlotArgs...)) {
    std::cout << "Current return type: " << typeid(ReturnType).name() << std::endl;

    


    //ccflow::CallbackConnector::inst().addConnection(signalInst, signal, slotInst, slot);



}