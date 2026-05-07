// src/SensorDriver.cpp
#include "SensorDriver.hpp"

void SensorDriver::pushEventFromISR(InterruptType type, uint32_t value) {
    InterruptEvent event {
        type,
        fakeTimestamp_++,
        value
    };

    queue_.pushFromISR(event);
}

void SensorDriver::onDataReadyISR(uint32_t value) {
    pushEventFromISR(InterruptType::DataReady, value);
}

void SensorDriver::onThresholdISR(uint32_t value) {
    pushEventFromISR(InterruptType::ThresholdExceeded, value);
}

void SensorDriver::onErrorISR(uint32_t errorCode) {
    pushEventFromISR(InterruptType::SensorError, errorCode);
}

void SensorDriver::onTimerTickISR(uint32_t tick) {
    pushEventFromISR(InterruptType::TimerTick, tick);
}

bool SensorDriver::getNextEvent(InterruptEvent& event) {
    return queue_.pop(event);
}

uint32_t SensorDriver::overflowCount() const {
    return queue_.overflowCount();
}