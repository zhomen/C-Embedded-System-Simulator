// include/SensorDriver.hpp
#pragma once

#include "InterruptRingBuffer.hpp"

class SensorDriver {
public:
    void onDataReadyISR(uint32_t value);
    void onThresholdISR(uint32_t value);
    void onErrorISR(uint32_t errorCode);
    void onTimerTickISR(uint32_t tick);

    bool getNextEvent(InterruptEvent& event);
    uint32_t overflowCount() const;

private:
    static constexpr std::size_t QueueSize = 8;
    InterruptRingBuffer<QueueSize> queue_;

    uint32_t fakeTimestamp_ = 0;

    void pushEventFromISR(InterruptType type, uint32_t value);
};