# C++ Embedded System Simulator (C++ + Python Tests)

## Overview

This project is a **host-based simulation of embedded interrupt-driven sensor systems** written in modern C++. It is designed specifically for:

- Practicing embedded systems concepts
- Demonstrating ISR (Interrupt Service Routine) best practices
- Testing interrupt-driven designs without hardware

The project simulates:

- Multiple interrupt sources
- ISR behavior (minimal work)
- Deferred processing using a ring buffer
- Event-driven architecture
- Python-based unit testing for C++ code

---

## Key Concepts Demonstrated

### Interrupt Handling
- ISR does **minimal work only**
- No blocking, allocation, or I/O inside ISR
- Work deferred to main loop

### Ring Buffer (ISR-safe)
- Lock-free design using atomics
- Single-producer (ISR) / single-consumer (main loop)
- Overflow detection

### Multiple Interrupt Types
- Data ready
- Threshold exceeded
- Sensor error
- Timer tick

### Testability
- Hardware abstracted via `InterruptController`
- Fully testable on host machine
- Python tests compile and validate behavior

---

## Project Structure

```text
sensor-interrupt-sim/
├── include/            # Public headers
├── src/                # Implementation files
├── tests/              # Python tests
├── CMakeLists.txt
```

---

## Build Instructions

### Requirements

- C++17 compiler (g++, clang)
- CMake >= 3.16
- Python 3
- pytest

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run Simulator

```bash
./sensor_sim
```

---

## Running Tests

Install pytest:

```bash
pip install pytest
```

Run tests:

```bash
pytest tests
```

The Python tests will:
- Build the project
- Compile small C++ test programs
- Execute them and verify behavior

---

## Architecture

### Data Flow

```text
SensorSimulator
      ↓
InterruptController
      ↓
ISR (SensorDriver::onXISR)
      ↓
Ring Buffer (InterruptRingBuffer)
      ↓
Main Loop / Consumer
```

---

## ISR Design Example

```cpp
void SensorDriver::onDataReadyISR(uint32_t value) {
    pushEventFromISR(InterruptType::DataReady, value);
}
```

ISR rules followed:
- No logging
- No dynamic allocation
- Constant-time execution

---

## Ring Buffer Behavior

- Fixed-size circular buffer
- Drops events on overflow
- Tracks overflow count

```cpp
bool pushFromISR(const InterruptEvent& event);
bool pop(InterruptEvent& event);
```

---

## Possible Extensions

- Add RTOS-style task handling
- Simulate interrupt priorities
- Add DMA-style bulk transfers
- Replace ring buffer with queue + mutex (compare performance)
- Add timing constraints / latency measurement

---