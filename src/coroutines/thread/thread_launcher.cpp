#include "include/coroutines/thread/thread_launcher.h"

ccflow::ThreadLauncher::ThreadLauncher()
    : ccflow::LauncherDerived<ccflow::ThreadLauncher>("ccflow::ExecThread") {
}

ccflow::ThreadLauncher::~ThreadLauncher() {
}
