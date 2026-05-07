#include "Interrupt.hpp"

class Interrupt
{
public:
    Interrupt() = default;
    ~Interrupt() = default;

    std::queue<InterruptType> interrupt_queue;

    // Dispatch and handle all interrupts in the queue
    void dispatch(InterruptType type)
    {
        switch(type)
        {
            case TIMER:
                handle_timer_interrupt();
                break;
            case READY:
                handle_ready_interrupt();
                break;
            case ERROR:
                handle_error_interrupt();
                break;
            case SHUTDOWN:
                handle_shutdown_interrupt();
                break;
            default:
                std::cout << "Unknown interrupt type!" << std::endl;
        }
    }

    void handle_timer_interrupt()
    {
        std::cout << "Handling TIMER interrupt: Timer tick!" << std::endl;
    }

    void handle_ready_interrupt()
    {
        std::cout << "Handling READY interrupt: Sensor is ready!" << std::endl;
    }

    void handle_error_interrupt()
    {
        std::cout << "Handling ERROR interrupt: An error occurred!" << std::endl;
    }

    void handle_shutdown_interrupt()
    {
        std::cout << "Handling SHUTDOWN interrupt: System is shutting down!" << std::endl;
    }

     // Register a handler for a specific interrupt type
};