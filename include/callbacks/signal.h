#pragma once

#include <mutex>

#include "callback_handler.h"

namespace ccflow {

template <class... SignalArgs>
class Signal : public CallbackHandler<void, SignalArgs...> {
public:
    Signal() : CallbackHandler<void, SignalArgs...>(){};
    void emit(SignalArgs &&...args) {
        for (auto &elem : Signal::getSlots()) {
            elem->run(std::forward<SignalArgs>(args)...);
        }
    }
};

}  // namespace ccflow