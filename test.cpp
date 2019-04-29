#include "stopwatch.hpp"

#include <iostream>

int main()
{
    Stopwatch stopwatch;
    stopwatch.start();

    std::cout << "duration: " << stopwatch.split().count() << " seconds" << std::endl;
    std::cout << "current_time: " << Stopwatch::current_time << std::endl;

    stopwatch.stop();
}
