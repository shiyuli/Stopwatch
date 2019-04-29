#include "stopwatch.hpp"

#include <iostream>

int main()
{
    Stopwatch stopwatch;
    stopwatch.start();
    sleep(2);

    std::cout << "duration: " << stopwatch.split() << " seconds" << std::endl;

    duration_t duration = stopwatch.split_raw();
    std::cout << "duration: " << duration.count() << " seconds" << std::endl;

    std::cout << "current_time: " << Stopwatch::now << std::endl;

    std::cout << stopwatch.splits() << std::endl;

    stopwatch.stop();
}
