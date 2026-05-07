// include/InterruptRingBuffer.hpp
#pragma once

#include "InterruptEvent.hpp"
#include <array>
#include <atomic>
#include <cstddef>

template <std::size_t Capacity>
class InterruptRingBuffer {
public:
    bool pushFromISR(const InterruptEvent& event) {
        const auto head = head_.load(std::memory_order_relaxed);
        const auto next = (head + 1) % Capacity;

        if (next == tail_.load(std::memory_order_acquire)) {
            overflowCount_.fetch_add(1);
            return false;
        }

        buffer_[head] = event;
        head_.store(next, std::memory_order_release);
        return true;
    }

    bool pop(InterruptEvent& event) {
        const auto tail = tail_.load(std::memory_order_relaxed);

        if (tail == head_.load(std::memory_order_acquire)) {
            return false;
        }

        event = buffer_[tail];
        tail_.store((tail + 1) % Capacity, std::memory_order_release);
        return true;
    }

    uint32_t overflowCount() const {
        return overflowCount_.load();
    }

    bool empty() const {
        return head_.load() == tail_.load();
    }

private:
    std::array<InterruptEvent, Capacity> buffer_{};
    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};
    std::atomic<uint32_t> overflowCount_{0};
};