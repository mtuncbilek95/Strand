/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Data/Definitions/Definitions.h>
#include <Runtime/Data/Definitions/StdNames.h>
#include <Runtime/Data/Containers/Singleton.h>

#include <spdlog/spdlog.h>

namespace Flax
{
    enum class LogType
    {
        IO,
        Window,
        Editor,
        Render,
        Resource,
        VFS,
        ECS,
        Reflection,
        Thread,
        Input,
        Memory,
        ShaderCompiler,
        StandardLib,
        General,
        Game
    };

    class LoggerWorker final : public Singleton<LoggerWorker>
    {
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