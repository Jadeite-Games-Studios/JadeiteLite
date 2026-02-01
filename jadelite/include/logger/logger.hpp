#pragma once

#define JADE_LOG( x, ... ) \
    Jadeite::Logging::Logger::GetInstance().Log( x __VA_OPT__(, ) __VA_ARGS__ )
#define JADE_WARN( x, ... ) \
    Jadeite::Logging::Logger::GetInstance().Warn( x __VA_OPT__(, ) __VA_ARGS__ )

#define JADE_ERROR( x, ... )                                                        \
    Jadeite::Logging::Logger::GetInstance().Error( std::source_location::current(), \
                                                   x __VA_OPT__(, ) __VA_ARGS__ )

#define JADE_ASSERT( x ) assert( x )
#define JADE_INIT_LOGS( console, retain ) \
    Jadeite::Logging::Logger::GetInstance().Init( console, retain )

#define JADE_GET_LOGS() Jadeite::Logging::Logger::GetInstance().GetLogs()
#define JADE_CLEAR_LOGS() Jadeite::Logging::Logger::GetInstance().ClearLogs()

namespace Jadeite::Logging
{

struct LogEntry;

class Logger
{

public:
    static Logger& GetInstance();

    // Make the logger non-copyable
    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;

    void Init( bool consoleLog = true, bool retainLogs = true );

    template <typename... Args>
    void Log( const std::string_view message, Args&&... args );

    template <typename... Args>
    void Warn( const std::string_view message, Args&&... args );

    template <typename... Args>
    void Error( std::source_location location, const std::string_view message, Args&&... args );

    template <typename... Args>
    void Error( const std::string_view message, Args&&... args );

    inline void ClearLogs()
    {
        m_LogEntries.clear();
    }

    inline const std::vector<LogEntry>& GetLogs()
    {
        return m_LogEntries;
    }

private:
    std::mutex m_Mutex;
    std::vector<LogEntry> m_LogEntries;
    bool m_bInitialized{ false };
    bool m_bConsoleLog{ true };
    bool m_bRetainLogs{ true };

    struct LogTime
    {
        std::string day, dayNumber, month, year, time;
        LogTime( const std::string& date );
    };

private:
    std::string CurrentDateTime();
    Logger() = default;
    ~Logger() = default;
};

struct LogEntry
{
    enum class LogType
    {
        INFO,
        WARN,
        ERR,
        NONE
    };
    LogType type{ LogType::INFO };
    std::string log{};
};

} // namespace Jadeite::Logging

#include "logger.inl"
