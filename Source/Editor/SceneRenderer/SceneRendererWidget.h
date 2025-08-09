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
	class SceneRendererView;
	class SceneToolView;

	class SceneRendererWidget : public QWidget
	{
		Q_OBJECT
	public:
		SceneRendererWidget(QWidget* pParent = nullptr);
		~SceneRendererWidget();

	private slots:
		void onClickedPlay();
		void onClickedPause();
		void onClickedStop();

	private:
		void setupSignals();

	private:
		SceneRendererView* m_renderView;
		SceneToolView* m_toolView;
	};
}
