#include "core/Log.h"
#include <iostream>

void Log::Init()
{
    std::cout << "[CoffeeEngine] Log Iniciado\n";
}

void Log::Shutdown()
{
    std::cout << "[CoffeeEngine] Log Finalizado\n";
}
