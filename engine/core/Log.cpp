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

void Log::Message(LogLevel level, const std::string &msg)
{
    switch (level)
    {
    case LogLevel::Info:
        std::cout << "\033[32m[INFO]\033[0m " << msg << "\n"; // verde
        break;

    case LogLevel::Warning:
        std::cout << "\033[33m[WARN]\033[0m " << msg << "\n"; // amarelo
        break;

    case LogLevel::Error:
        std::cerr << "\033[31m[ERROR]\033[0m " << msg << "\n"; // vermelho
        break;
    }
}