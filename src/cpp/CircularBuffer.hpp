#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class CircularBuffer 
{
public:
    explicit CircularBuffer(size_t capacity);

    void push(const T& item);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const;
    bool full() const;
    size_t size() const;

private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
};