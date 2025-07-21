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
	class SceneRendererView : public QWidget
	{
		Q_OBJECT
	public:
		SceneRendererView(QWidget* pParent = nullptr);
		~SceneRendererView();


	protected:
		void resizeEvent(QResizeEvent* event) override;

	private:
	};
}
