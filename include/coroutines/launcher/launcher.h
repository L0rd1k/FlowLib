#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include "definitions/definitions.h"
#include "result.h"

namespace ccflow {

class CCFLOW_API Launcher {
public:
    Launcher(std::string_view name)
        : name_(name) {
    }
    virtual ~Launcher() noexcept = default;

protected:
    template <class CallableType, class... Args>
    auto submit(CallableType&& callable, Args&&... args) {
        return submiting<Launcher>(std::forward<CallableType>(callable),
                                   std::forward<Args>(args)...);
    }

    /** @brief **/
    template <class ExecType, class CallableType, class... Args>
    auto submiting(CallableType&& signal, Args&&... args) {
        std::cout << "Submitting" << std::endl;

        static_assert(std::is_invocable_v<CallableType, Args...>,
                      "<<CallableType>> can't be invoke with <<Args...>>");

        using return_type = typename std::invoke_result_t<CallableType, Args...>;
        return submit_bridge<return_type>({},
                                          *static_cast<ExecType*>(this),
                                          std::forward<CallableType>(signal),
                                          std::forward<Args>(args)...);
    }


private:
    template <class ReturnType, class ExecType, class CallableType, class... Args>
    static Result<ReturnType> submit_bridge(ExecTag, ExecType&, CallableType callable, Args... args) {
        // co_return callable(arguments...);
    }

private:
    const std::string name_;
};

}  // namespace ccflow