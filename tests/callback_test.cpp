#include "include/callbacks/callback.h"

#include <gtest/gtest.h>

#include <memory>
#include <thread>

#include "include/callbacks/signal.h"

TEST(CallbacksSamples, ConnectTest1) {
    class Handler {
    public:
        Handler() = default;
        void onReceive() { value++; }
        int value = 49;
    } handler;

    std::unique_ptr<Handler> obj = std::make_unique<Handler>();
    ccflow::Signal<> signal;
    connect(&signal, &handler, &Handler::onReceive);
    signal.emit();
    EXPECT_EQ(50, handler.value);
}

TEST(CallbacksSamples, ConnectTest2) {
    class Handler {
    public:
        void onReceive(int &v1, int v2) { v1 += v2; }
    } handler;

    int testValue = 5;
    ccflow::Signal<int &, int> signal;
    connect(&signal, &handler, &Handler::onReceive);
    signal.emit(testValue, 45);
    EXPECT_EQ(50, testValue);
}

TEST(CallbacksSamples, ConnectTest3) {
    
}
