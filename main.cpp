#include "programConfig.h"

#if USING_OOP
    #include "oopVersion/app.hpp"
#endif // USING_OOP

#include <iostream>

int main(int argc, char* argv[])
{
#if PROFILING
    std::cout << "Profiling enabled\n";
#endif // PROFILING

#if USING_OOP
    Application app;

    if (!app.setup())
    {
        std::cout << "Setup failed\n";
        return 1;
    }

    app.loop();
#endif // USING_OOP

    return 0;
}
