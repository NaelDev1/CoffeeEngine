#pragma once
#include <string>
#include <iostream>

enum class LogLevel
{
    Info,
    Warning,
    Error
};

class Log
{
public:
    static void Init();
    static void Shutdown();

    template <typename... Zezinho>
    static void Message(LogLevel level, Zezinho &&...args)
    {
        switch (level)
        {
        case LogLevel::Info:
            std::cout << "\033[32m[INFO]\033[0m ";
            break;
        case LogLevel::Warning:
            std::cout << "\033[33m[WARN]\033[0m ";
            break;
        case LogLevel::Error:
            std::cout << "\033[31m[ERROR]\033[0m ";
            break;
        }

        (std::cout << ... << args) << "\n";
    }
};

#define LOG_INFO(...) Log::Message(LogLevel::Info, __VA_ARGS__);
#define LOG_WARN(...) Log::Message(LogLevel::Warning, __VA_ARGS__);
#define LOG_ERROR(...) Log::Message(LogLevel::Error, __VA_ARGS__);
