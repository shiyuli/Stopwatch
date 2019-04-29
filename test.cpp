#include "stopwatch.hpp"

#include <iostream>

int main()
{
    Stopwatch stopwatch;
    stopwatch.start();

    std::cout << "duration: " << stopwatch.split().count() << std::endl;
}
