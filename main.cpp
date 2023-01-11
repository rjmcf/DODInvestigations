#include "oopVersion/app.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    Application app;

    if (!app.setup())
    {
        std::cout << "Setup failed\n";
        return 1;
    }

    app.loop();

    return 0;
}
