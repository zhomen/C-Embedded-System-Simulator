// include/InterruptController.hpp
#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

class InterruptController {
public:
    using ISR = std::function<void(uint32_t value)>;

    void registerISR(uint32_t irqNumber, ISR isr);
    void trigger(uint32_t irqNumber, uint32_t value);

private:
    std::unordered_map<uint32_t, ISR> isrTable_;
};