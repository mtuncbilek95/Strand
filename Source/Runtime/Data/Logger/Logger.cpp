#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Flax
{
    LoggerWorker::LoggerWorker()
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%^%l%$][%n] %v");

        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.txt", true);
        fileSink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%l][%n] %v");

        auto create_logger = [&](const std::string& name, spdlog::level::level_enum printLevel)
            {
                auto logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{ consoleSink, fileSink });
                logger->set_level(printLevel);
                logger->flush_on(printLevel);
                return logger;
            };

        m_loggers[LogType::IO] = create_logger("IO", spdlog::level::debug);
        m_loggers[LogType::Window] = create_logger("Window", spdlog::level::debug);
        m_loggers[LogType::Editor] = create_logger("Editor", spdlog::level::debug);
        m_loggers[LogType::GfxContext] = create_logger("GfxContext", spdlog::level::debug);
        m_loggers[LogType::GraphicsAPI] = create_logger("GraphicsAPI", spdlog::level::info);
        m_loggers[LogType::Render] = create_logger("Render", spdlog::level::debug);
        m_loggers[LogType::Resource] = create_logger("Resource", spdlog::level::debug);
        m_loggers[LogType::VFS] = create_logger("VFS", spdlog::level::debug);
        m_loggers[LogType::ECS] = create_logger("ECS", spdlog::level::debug);
        m_loggers[LogType::Reflection] = create_logger("AssetManager", spdlog::level::debug);
        m_loggers[LogType::Executor] = create_logger("Executor", spdlog::level::debug);
        m_loggers[LogType::Thread] = create_logger("Thread", spdlog::level::debug);
        m_loggers[LogType::Input] = create_logger("Input", spdlog::level::debug);
        m_loggers[LogType::Memory] = create_logger("Memory", spdlog::level::debug);
        m_loggers[LogType::ShaderCompiler] = create_logger("ShaderCompiler", spdlog::level::debug);
        m_loggers[LogType::StandardLib] = create_logger("StandardLib", spdlog::level::debug);
        m_loggers[LogType::General] = create_logger("General", spdlog::level::debug);
        m_loggers[LogType::Importer] = create_logger("Importer", spdlog::level::debug);
        m_loggers[LogType::Game] = create_logger("Game", spdlog::level::debug);
    }

    LoggerWorker::~LoggerWorker()
    {

    }
}
