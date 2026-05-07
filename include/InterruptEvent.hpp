// include/InterruptEvent.hpp
#pragma once
#include <cstdint>

enum class InterruptType {
    DataReady,
    ThresholdExceeded,
    SensorError,
    TimerTick
};

struct InterruptEvent {
    InterruptType type;
    uint32_t timestamp;
    uint32_t value;
};