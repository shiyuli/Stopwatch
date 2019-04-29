#include "stopwatch.hpp"

#include <cstdlib>
#include <iostream>

int main()
{
    Stopwatch* stopwatch = new Stopwatch();
    stopwatch->start();
    std::cout << "duration: " << stopwatch->split().count() << std::endl;

    system("pause");
}
