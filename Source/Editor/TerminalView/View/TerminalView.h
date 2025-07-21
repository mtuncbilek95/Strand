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
	class TerminalView : public QWidget
	{
		Q_OBJECT
	public:
		TerminalView(QWidget* pParent = nullptr);
		~TerminalView();

	private slots:
		void OnLogMessageReceived(const QString& msg, const QString& category, int level);
		void OnCommandEntered();

	private:
		void connectSignals();

	private:
		QTextEdit* m_textEdit;
		QLineEdit* m_lineEdit;
	};
}
