/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>
#include <Editor/Data/Vector/ValueWidget.h>

namespace Strand
{
	class Vector4Widget : public QWidget
	{
		Q_OBJECT
	public:
		Vector4Widget(const QString& name, QWidget* pParent = nullptr);
		~Vector4Widget() override = default;

	private:
		QLabel* m_nameLabel;
		ValueWidget* m_xSlider;
		ValueWidget* m_ySlider;
		ValueWidget* m_zSlider;
		ValueWidget* m_wSlider;
	};
}