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
