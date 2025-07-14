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
	class ProjectBrowserModel;
	class ProjectBrowserView;

	class ProjectBrowserViewModel : public ViewModelBase
	{
		Q_OBJECT;
	public:
		ProjectBrowserViewModel(QObject* pParent = nullptr);
		~ProjectBrowserViewModel();

		void SetModel(ProjectBrowserModel* model) { m_model = model; }
		ProjectBrowserModel* Model() const { return m_model; }

	signals:
		void setCurrentIndex(const QModelIndex& index);

	public slots:
		void onItemSelected(const QModelIndex& index);
		void onItemDoubleClicked(const QModelIndex& index);
		void onItemContextMenuRequested(const QModelIndex& index);

	private:
		ProjectBrowserModel* m_model;
	};
}
