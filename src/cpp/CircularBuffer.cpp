#include "CircularBuffer.hpp"

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t capacity)
        : buffer(capacity), head(0), tail(0), count(0), capacity(capacity) {}

    void push(const T& item) {
        if (full()) {
            throw std::runtime_error("Buffer is full");
        }
        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        ++count;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Buffer is empty");
        }
        head = (head + 1) % capacity;
        --count;
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("Buffer is empty");
        }
        return buffer[head];
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Buffer is empty");
        }
        return buffer[head];
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == capacity;
    }

    size_t size() const {
        return count;
    }

private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
};