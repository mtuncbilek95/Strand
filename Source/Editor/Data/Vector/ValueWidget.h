/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>
#include <Editor/Data/Vector/NumberValueType.h>

namespace Strand
{
	class ValueWidget : public QWidget
	{
		Q_OBJECT
	public:
		ValueWidget(const QString& name, NumberValueType type, QWidget* pParent = nullptr);
		~ValueWidget() override = default;

	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;

	private:
		QLabel* m_nameLabel;
		QDoubleSpinBox* m_value;
		b8 m_isDragging = false;
		QPoint m_dragStartPosition;
	};
}