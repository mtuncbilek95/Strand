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
	class DomainListView;
	class DomainMiscView;
	class DomainFilterProxy;
	class DomainIconProvider;

	class DomainViewWidget : public QWidget
	{
		Q_OBJECT
	public:
		DomainViewWidget(QWidget* pParent = nullptr);
		~DomainViewWidget();

	signals:
		void onRefreshPathView(const QString& path);
		void onFileActivated(const QString& filePath);

	private slots:
		void onAddDomainClicked();
		void onImportDomainClicked();
		void onBackDomainClicked();
		void onDomainActivated(const QModelIndex& proxyIndex);
		void onPathViewClicked(const QString& path);
		
	private:
		void setupSignals();
		
	private:
		DomainListView* m_listView;
		DomainMiscView* m_miscView;
		DomainFilterProxy* m_proxy;
		DomainIconProvider* m_provider;

		QFileSystemModel m_fsModel;
	};
}
