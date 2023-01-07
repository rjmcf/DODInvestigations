#include "app.hpp"

int main(int argc, char* argv[])
{
    Application app;

    if (!app.setup())
    {
        return 1;
    }

    app.loop();

    return EXIT_SUCCESS;
}
