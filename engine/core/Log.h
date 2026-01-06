#pragma once
#include <string>

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

    static void Message(LogLevel level, const std::string &msg);
};

#define LOG_INFO(msg) Log::Message(LogLevel::Info, msg);
#define LOG_WARN(msg) Log::Message(LogLevel::Warning, msg);
#define LOG_ERROR(msg) Log::Message(LogLevel::Error, msg);
