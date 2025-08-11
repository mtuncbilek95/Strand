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
	class Vector3Widget : public QWidget
	{
		Q_OBJECT
	public:
		Vector3Widget(QWidget* pParent = nullptr);
		~Vector3Widget() override = default;

	private:
		QSlider* m_xSlider;
		QSlider* m_ySlider;
		QSlider* m_zSlider;
	};
}