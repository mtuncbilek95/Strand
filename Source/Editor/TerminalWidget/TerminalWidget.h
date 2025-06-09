/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/Data/LogSink/QLogSink.h>

namespace Flax
{
	using QSink = QLogSink<Mutex>;

	class TerminalWidget : public QWidget
	{
		Q_OBJECT
	public:
		TerminalWidget(QWidget* pParent = nullptr);
		~TerminalWidget();

	private slots:
		void OnLogMessageReceived(const QString& msg, const QString& category, int level);

	private:
		QTextEdit* m_textEdit;
	};
}
