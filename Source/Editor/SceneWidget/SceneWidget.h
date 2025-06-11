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

#include <Runtime/Graphics/Context/GfxContext.h>

namespace Flax
{
	/**
	 * @class SceneWidget
	 * @brief It will show the current scene that engine tries to render. It will be anchor point of the renderer for editor.
	 */
	class SceneWidget : public QWidget
	{
		Q_OBJECT
	public:
		SceneWidget(QWidget* pParent = nullptr);
		~SceneWidget();

	public slots:
		void RunScene();

	protected:
		void resizeEvent(QResizeEvent* event) override final;

	private:
		GfxContext* m_ctx;
	};
}