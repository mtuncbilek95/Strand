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
	class ProjectBrowserViewModel;
	class ProjectBreadcrumbsView;

	class ProjectBrowserView : public QWidget
	{
		Q_OBJECT
		friend class ProjectBrowserViewModel;
	public:
		ProjectBrowserView(QWidget* pParent = nullptr);
		~ProjectBrowserView();

	private:
		QListView* m_listView;
		ProjectBrowserViewModel* m_viewModel;
		ProjectBreadcrumbsView* m_breadcrumbs;
	};
}
