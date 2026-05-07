// src/InterruptController.cpp
#include "InterruptController.hpp"

void InterruptController::registerISR(uint32_t irqNumber, ISR isr) {
    isrTable_[irqNumber] = isr;
}

void InterruptController::trigger(uint32_t irqNumber, uint32_t value) {
    auto it = isrTable_.find(irqNumber);
    if (it != isrTable_.end()) {
        it->second(value);
    }
}