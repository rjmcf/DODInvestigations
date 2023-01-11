#include "oopVersion/app.hpp"

#include "profilingConfig.h"

#include <iostream>

int main(int argc, char* argv[])
{
#if PROFILING
    std::cout << "Profiling enabled\n";
#endif // PROFILING

    Application app;

    if (!app.setup())
    {
        std::cout << "Setup failed\n";
        return 1;
    }

    app.loop();

    return 0;
}
