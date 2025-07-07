/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/TerminalConsole/ViewModel/LogSinkViewModel.h>

#include <spdlog/sinks/base_sink.h>

namespace Flax
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