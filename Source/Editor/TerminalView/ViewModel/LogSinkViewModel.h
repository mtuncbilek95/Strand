/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Flax
{
	class LogSinkViewModel : public ViewModelBase
	{
		Q_OBJECT
	public:
		LogSinkViewModel(QObject* pParent = nullptr);
		~LogSinkViewModel();

	signals:
		void LogMessageReceived(const QString& msg, const QString& category, int level);
		void LogCommandExecuted(const QString& command, const QString& value);

	private slots:
		void OnLogCommandExecuted(const QString& command, const QString& value);
	};
}