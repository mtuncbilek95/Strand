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
	class Vector3Widget;

	class TransformWidget : public QWidget
	{
		Q_OBJECT
	public:
		TransformWidget(QWidget* pParent = nullptr);
		~TransformWidget();

	private:
		Vector3Widget* m_position;
		Vector3Widget* m_rotation;
		Vector3Widget* m_scale;
	};
}
