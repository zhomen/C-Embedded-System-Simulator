// src/SensorSimulator.cpp
#include "SensorSimulator.hpp"

SensorSimulator::SensorSimulator(InterruptController& controller)
    : controller_(controller) {}

void SensorSimulator::dataReady(uint32_t value) {
    controller_.trigger(DATA_READY_IRQ, value);
}

void SensorSimulator::thresholdExceeded(uint32_t value) {
    controller_.trigger(THRESHOLD_IRQ, value);
}

void SensorSimulator::sensorError(uint32_t errorCode) {
    controller_.trigger(ERROR_IRQ, errorCode);
}

void SensorSimulator::timerTick(uint32_t tick) {
    controller_.trigger(TIMER_IRQ, tick);
}