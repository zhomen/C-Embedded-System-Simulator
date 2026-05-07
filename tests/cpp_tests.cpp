// tests/cpp_tests.cpp
#include "InterruptController.hpp"
#include "SensorDriver.hpp"
#include "SensorSimulator.hpp"

#include <cassert>
#include <iostream>

void registerISRs(InterruptController& interrupts, SensorDriver& driver) {
    interrupts.registerISR(SensorSimulator::DATA_READY_IRQ,
        [&driver](uint32_t value) { driver.onDataReadyISR(value); });

    interrupts.registerISR(SensorSimulator::THRESHOLD_IRQ,
        [&driver](uint32_t value) { driver.onThresholdISR(value); });

    interrupts.registerISR(SensorSimulator::ERROR_IRQ,
        [&driver](uint32_t value) { driver.onErrorISR(value); });

    interrupts.registerISR(SensorSimulator::TIMER_IRQ,
        [&driver](uint32_t value) { driver.onTimerTickISR(value); });
}

void test_data_ready_interrupt() {
    InterruptController interrupts;
    SensorDriver driver;
    SensorSimulator sensor(interrupts);

    registerISRs(interrupts, driver);

    sensor.dataReady(123);

    InterruptEvent event;
    assert(driver.getNextEvent(event));
    assert(event.type == InterruptType::DataReady);
    assert(event.value == 123);
}

void test_multiple_interrupt_types_ordered() {
    InterruptController interrupts;
    SensorDriver driver;
    SensorSimulator sensor(interrupts);

    registerISRs(interrupts, driver);

    sensor.dataReady(10);
    sensor.thresholdExceeded(99);
    sensor.sensorError(5);

    InterruptEvent event;

    assert(driver.getNextEvent(event));
    assert(event.type == InterruptType::DataReady);
    assert(event.value == 10);

    assert(driver.getNextEvent(event));
    assert(event.type == InterruptType::ThresholdExceeded);
    assert(event.value == 99);

    assert(driver.getNextEvent(event));
    assert(event.type == InterruptType::SensorError);
    assert(event.value == 5);
}

void test_ring_buffer_overflow() {
    SensorDriver driver;

    for (int i = 0; i < 20; ++i) {
        driver.onDataReadyISR(i);
    }

    assert(driver.overflowCount() > 0);
}

void test_empty_queue() {
    SensorDriver driver;
    InterruptEvent event;

    assert(driver.getNextEvent(event) == false);
}

int main() {
    test_data_ready_interrupt();
    test_multiple_interrupt_types_ordered();
    test_ring_buffer_overflow();
    test_empty_queue();

    std::cout << "All C++ tests passed\n";
}