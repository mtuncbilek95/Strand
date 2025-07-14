#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/bundled/ostream.h>

namespace Flax
{
    LoggerWorker::LoggerWorker()
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%^%l%$][%n] %v");

        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.txt", true);
        fileSink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%l][%n] %v");

        auto createLogger = [&](const std::string& name, spdlog::level::level_enum printLevel)
            {
                auto logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{ consoleSink, fileSink });
                logger->set_level(printLevel);
                logger->flush_on(printLevel);
                return logger;
            };

        m_loggers[LogType::Application] = createLogger("Application", spdlog::level::debug);
        m_loggers[LogType::IO] = createLogger("IO", spdlog::level::debug);
        m_loggers[LogType::Window] = createLogger("Window", spdlog::level::debug);
        m_loggers[LogType::Editor] = createLogger("Editor", spdlog::level::debug);
        m_loggers[LogType::Engine] = createLogger("Engine", spdlog::level::debug);
        m_loggers[LogType::GfxContext] = createLogger("GfxContext", spdlog::level::debug);
        m_loggers[LogType::GraphicsAPI] = createLogger("GraphicsAPI", spdlog::level::info);
        m_loggers[LogType::Render] = createLogger("Render", spdlog::level::debug);
        m_loggers[LogType::Resource] = createLogger("Resource", spdlog::level::debug);
        m_loggers[LogType::Asset] = createLogger("Asset", spdlog::level::debug);
        m_loggers[LogType::ECS] = createLogger("ECS", spdlog::level::debug);
        m_loggers[LogType::VFS] = createLogger("VFS", spdlog::level::debug);
        m_loggers[LogType::FileSystem] = createLogger("FileSystem", spdlog::level::debug);
        m_loggers[LogType::Thread] = createLogger("Thread", spdlog::level::debug);
        m_loggers[LogType::Input] = createLogger("Input", spdlog::level::debug);
        m_loggers[LogType::ShaderCompiler] = createLogger("ShaderCompiler", spdlog::level::debug);
        m_loggers[LogType::Game] = createLogger("Game", spdlog::level::debug);
    }

    LoggerWorker::~LoggerWorker()
    {
    }
}
