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
	class SceneGraphTreeView;
	class SceneGraphModel;

	class SceneGraphWidget : public QWidget
	{
		Q_OBJECT
	public:
		SceneGraphWidget(QWidget* pParent = nullptr);
		~SceneGraphWidget();

	private:
		SceneGraphTreeView* m_treeView;
		SceneGraphModel* m_sgModel;
	};
}
