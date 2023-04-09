#pragma once

#include "launcher.h"

namespace ccflow {

template <class CExecType>
class CCFLOW_API LauncherDerived : public Launcher {
public:
    LauncherDerived(std::string_view name)
        : Launcher(name) {
    }

    template<class CallableType, class... Args>
    auto submit(CallableType&& callable, Args&&... args) {
        std::cout << "Submit" << std::endl;
        return submiting<CExecType>(std::forward<CallableType>(callable),
                                    std::forward<Args>(args)...);
    }
};

}  // namespace ccflow