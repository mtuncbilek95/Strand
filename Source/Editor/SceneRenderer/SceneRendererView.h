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
