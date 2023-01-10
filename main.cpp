#include "oopVersion/app.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting program\n";
    Application app;

    if (!app.setup())
    {
        std::cout << "Setup failed\n";
        return 1;
    }

    std::cout << "Start loop\n";
    app.loop();
    std::cout << "End loop\n";

    return 0;
}
