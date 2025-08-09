/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Strand
{
	class LogSinkViewModel : public ViewModelBase
	{
		Q_OBJECT
	public:
		LogSinkViewModel(QObject* pParent = nullptr);
		~LogSinkViewModel() override = default;

	signals:
		void LogMessageReceived(const QString& msg, const QString& category, int level);
		void LogCommandExecuted(const QString& command, const QString& value);

	private slots:
		void OnLogCommandExecuted(const QString& command, const QString& value);
	};
}