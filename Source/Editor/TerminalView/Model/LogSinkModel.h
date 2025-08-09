/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>
#include <Editor/TerminalView/ViewModel/LogSinkViewModel.h>

#include <spdlog/sinks/base_sink.h>

namespace Strand
{
	template<typename T, typename = std::enable_if_t<std::is_same_v<T, Mutex>>>
	class LogSinkModel : public spdlog::sinks::base_sink<T>
	{
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override final
		{
			spdlog::memory_buf_t formatted;
			this->formatter_->format(msg, formatted);

			QString qmsg = QString::fromStdString(fmt::to_string(formatted));
			QString category = QString::fromStdString(msg.logger_name.data());
			i32 level = static_cast<i32>(msg.level);

			auto vm = ViewModelRegistry::Get().ViewModel<LogSinkViewModel>();
			QMetaObject::invokeMethod(vm.get(), "LogMessageReceived",
				Qt::QueuedConnection,
				Q_ARG(QString, qmsg),
				Q_ARG(QString, category),
				Q_ARG(int, level));
		}

		void flush_() override final {}
	};
}