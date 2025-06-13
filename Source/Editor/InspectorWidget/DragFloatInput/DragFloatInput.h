/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/Core/CoreMinimal.h>

namespace Flax
{
	class DragFloatInput : public QWidget
	{
		Q_OBJECT
	public:
		DragFloatInput(const QColor& color = QColor("#8F2A2A"), f32 value = 0.f, QWidget* pParent = nullptr);
		~DragFloatInput();

	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void mouseDoubleClickEvent(QMouseEvent* event) override;

	private slots:
		void commitText();

	private:
		void updateDisplay();

	private:
		f32 m_value;
		QPoint m_mouseLastPos;
		QLabel* m_colorLabel;
		QLabel* m_dragLabel;
		QLineEdit* m_textLabel;
	};
}