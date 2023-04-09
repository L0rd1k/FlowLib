#pragma once

#include "include/coroutines/launcher/launcher.h"
#include "include/coroutines/launcher/launcher_derived.h"

namespace ccflow {

class ThreadLauncher : public LauncherDerived<ThreadLauncher> {
public:
    ThreadLauncher();
    virtual ~ThreadLauncher();

};

}  // namespace ccflow