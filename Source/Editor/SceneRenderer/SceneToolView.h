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
	class SceneToolView : public QWidget
	{
		Q_OBJECT
	public:
		SceneToolView(QWidget* pParent = nullptr);
		~SceneToolView() override = default;

	signals:
		void onPlaySignaled();
		void onPauseSignaled();
		void onStopSignaled();

	private:
		void setupSignals();

	private:
		QPushButton* m_playButton = nullptr;
		QPushButton* m_pauseButton = nullptr;
		QPushButton* m_stopButton = nullptr;
	};
}
