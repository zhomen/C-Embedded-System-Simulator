#pragma once
#include "Sensor.hpp"
#include <cstdlib>

enum SensorRegister
{
    VALUE = 0x00,
    STATUS = 0x01
};

class Sensor : public IDevice
{
private:
    int sensor_value = 0;
    bool sensor_ready = false;

public:
    void tick()
    {
        sensor_value = rand() % 100; // Simulate sensor value between 0 and 99
        if (rand() % 5 == 0) // Simulate a 20% chance of an error
        {
            sensor_ready = true; // Ready
            interrupt_queue.push(READY); // Trigger an interrupt to indicate the sensor is ready
        }
        else
        {
            sensor_ready = false; // Not ready
        }
    }

    void write_register(int addr, int value)
    {
        // Sensor registers are read-only, so we ignore any write attempts
    }

    int read_register(int addr) override
    {
        switch (addr)
        {
        case VALUE:
            return sensor_value;
        case STATUS:
            return sensor_ready ? 1 : 0; // Return 1 for ready, 0 for not ready
        default:
            return -1; // Invalid register address
        }
    }
};
