#pragma once
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <map>
#include <functional>

enum InterruptType
{
    TIMER = 0,
    READY = 1,
    ERROR = 2,
    SHUTDOWN = 3
};

class Interrupt
{
public:
    Interrupt() = default;
    ~Interrupt() = default;

    using Handler = std::function<void()>;

    // Add an interrupt to the queue
    void queue_interrupt(InterruptType type);

    // Register a handler for a specific interrupt type
    void register_handler(InterruptType type, Handler handler);

    // Dispatch and handle all interrupts in the queue
    void dispatch();

private:
    std::map<InterruptType, Handler> handlers;
};