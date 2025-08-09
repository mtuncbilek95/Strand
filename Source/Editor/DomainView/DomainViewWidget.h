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
