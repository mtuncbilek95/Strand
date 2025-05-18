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

        auto create_logger = [&](const std::string& name)
            {
                auto logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{ consoleSink, fileSink });
                logger->set_level(spdlog::level::debug);
                logger->flush_on(spdlog::level::debug);
                return logger;
            };

        m_loggers[LogType::IO] = create_logger("IO");
        m_loggers[LogType::Window] = create_logger("Window");
        m_loggers[LogType::Editor] = create_logger("Editor");
        m_loggers[LogType::GraphicsAPI] = create_logger("GraphicsAPI");
        m_loggers[LogType::Render] = create_logger("Render");
        m_loggers[LogType::Resource] = create_logger("Resource");
        m_loggers[LogType::VFS] = create_logger("VFS");
        m_loggers[LogType::ECS] = create_logger("ECS");
        m_loggers[LogType::Reflection] = create_logger("AssetManager");
        m_loggers[LogType::Thread] = create_logger("Thread");
        m_loggers[LogType::Input] = create_logger("Input");
        m_loggers[LogType::Memory] = create_logger("Memory");
        m_loggers[LogType::ShaderCompiler] = create_logger("ShaderCompiler");
        m_loggers[LogType::StandardLib] = create_logger("StandardLib");
        m_loggers[LogType::General] = create_logger("General");
        m_loggers[LogType::Importer] = create_logger("Importer");
        m_loggers[LogType::Game] = create_logger("Game");
    }

    LoggerWorker::~LoggerWorker()
    {

    }
}
