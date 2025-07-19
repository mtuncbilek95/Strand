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
	class ProjectBrowserFilterProxy;
	class ProjectBrowserIconProvider;

	class ProjectBrowserViewModel : public ViewModelBase
	{
		Q_OBJECT;
	public:
		ProjectBrowserViewModel(QObject* pParent = nullptr);
		~ProjectBrowserViewModel();

		ProjectBrowserIconProvider* IconProvider() const { return m_iconProvider; }
		QFileSystemModel* Model() const { return m_fileModel; }
		ProjectBrowserFilterProxy* Proxy() const { return m_proxy; }

	private:
		QFileSystemModel* m_fileModel;
		ProjectBrowserFilterProxy* m_proxy;
		ProjectBrowserIconProvider* m_iconProvider;
	};
}
