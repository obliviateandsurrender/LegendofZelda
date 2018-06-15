#include "timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double interval)
{
    this->prev = 0;
    this->interval = interval;
}

bool Timer::processTick()
{
    double cur = glfwGetTime();
    if (cur - this->prev - this->interval >= 0)
    {
        this->prev = cur;
        return true;
    }
    else
        return false;
}