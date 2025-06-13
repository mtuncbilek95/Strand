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
	class DragFloatInput;

	class Vector3Widget : public QWidget
	{
		Q_OBJECT
	public:
		Vector3Widget(QWidget* pParent = nullptr);
		~Vector3Widget();

	private:
		DragFloatInput* mXInput;
		DragFloatInput* mYInput;
		DragFloatInput* mZInput;
	};
}
