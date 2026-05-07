// src/main.cpp
#include "InterruptController.hpp"
#include "SensorDriver.hpp"
#include "SensorSimulator.hpp"

#include <iostream>

int main() {
    InterruptController interrupts;
    SensorDriver driver;
    SensorSimulator sensor(interrupts);

    interrupts.registerISR(SensorSimulator::DATA_READY_IRQ,
        [&driver](uint32_t value) { driver.onDataReadyISR(value); });

    interrupts.registerISR(SensorSimulator::THRESHOLD_IRQ,
        [&driver](uint32_t value) { driver.onThresholdISR(value); });

    interrupts.registerISR(SensorSimulator::ERROR_IRQ,
        [&driver](uint32_t value) { driver.onErrorISR(value); });

    interrupts.registerISR(SensorSimulator::TIMER_IRQ,
        [&driver](uint32_t value) { driver.onTimerTickISR(value); });

    sensor.dataReady(42);
    sensor.thresholdExceeded(90);
    sensor.sensorError(7);
    sensor.timerTick(1000);

    InterruptEvent event;

    while (driver.getNextEvent(event)) {
        std::cout << "Event type=" << static_cast<int>(event.type)
                  << " timestamp=" << event.timestamp
                  << " value=" << event.value
                  << "\n";
    }

    return 0;
}