#include <iostream>
#include "core/Application.h"
#include "core/Log.h"

int main()
{

    // std::cout << "CoffeEngine starting...\n";
    // return 0;

    Application app;
    Log::Init();
    app.Run();
    Log::Shutdown();
    return 0;
}