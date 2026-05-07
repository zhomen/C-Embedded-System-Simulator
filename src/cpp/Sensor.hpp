#pragma once
#include "IDevice.hpp"
#include "Interrupt.hpp"

extern std::queue<InterruptType> interrupt_queue;

class Sensor : public IDevice
{
public:
    Sensor() = default;
    ~Sensor() = default;

    void tick() override;
    void write_register(int addr, int value) override;
    int read_register(int addr) override;
};