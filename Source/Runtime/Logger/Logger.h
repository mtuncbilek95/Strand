/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Data/Containers/Singleton.h>

#include <spdlog/spdlog.h>

namespace Strand
{
    enum class LogType
    {
		Application,
        IO,
        Window,
        Editor,
		Engine,
        GfxContext,
        GraphicsAPI,
        Render,
        Resource,
		Reflection,
        Asset,
        ECS,
		VFS,
		FileSystem,
        Thread,
        Input,
        ShaderCompiler,
        Game
    };

	/**
	 * @class LoggerWorker
	 * @brief A log system powered by spdlog, which provides a 
	 * simple interface for logging messages of different types.
	 */
    class LoggerWorker final : public Singleton<LoggerWorker>
    {
		friend class TerminalView;
    public:
        LoggerWorker();
        ~LoggerWorker();

        template<typename... Args>
        void LogInfo(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            m_loggers[type]->info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void LogDebug(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            m_loggers[type]->debug(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void LogWarn(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            m_loggers[type]->warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void LogError(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            m_loggers[type]->error(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void LogCritical(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            m_loggers[type]->critical(fmt, std::forward<Args>(args)...);
        }

		
    private:
        HashMap<LogType, std::shared_ptr<spdlog::logger>> m_loggers;
    };

    namespace Log
    {
        template<typename... Args>
        void Info(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            LoggerWorker::Get().LogInfo(type, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Debug(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            LoggerWorker::Get().LogDebug(type, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Warn(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            LoggerWorker::Get().LogWarn(type, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Error(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            LoggerWorker::Get().LogError(type, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Critical(LogType type, spdlog::format_string_t<Args...> fmt, Args&&... args)
        {
            LoggerWorker::Get().LogCritical(type, fmt, std::forward<Args>(args)...);
        }
    }
}