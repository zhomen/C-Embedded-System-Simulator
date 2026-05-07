// include/SensorSimulator.hpp
#pragma once

#include "InterruptController.hpp"
#include <cstdint>

class SensorSimulator {
public:
    SensorSimulator(InterruptController& controller);

    void dataReady(uint32_t value);
    void thresholdExceeded(uint32_t value);
    void sensorError(uint32_t errorCode);
    void timerTick(uint32_t tick);

    static constexpr uint32_t DATA_READY_IRQ = 1;
    static constexpr uint32_t THRESHOLD_IRQ  = 2;
    static constexpr uint32_t ERROR_IRQ      = 3;
    static constexpr uint32_t TIMER_IRQ      = 4;

private:
    InterruptController& controller_;
};