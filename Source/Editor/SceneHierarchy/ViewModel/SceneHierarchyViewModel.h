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
	class Scene;
	class SceneHierarchyModel;

	class SceneHierarchyViewModel : public ViewModelBase
	{
		Q_OBJECT
	public:
		SceneHierarchyViewModel(QObject* pParent = nullptr);
		~SceneHierarchyViewModel();

		void SetScene(Scene* scene);
		SceneHierarchyModel* Model() const { return m_model; }

	public slots:
		void onContextMenuRequested(const QPoint& pos);

	private:
		SceneHierarchyModel* m_model;
	};
}
