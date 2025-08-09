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
	class DomainPathView;

	class DomainMiscView : public QWidget
	{
		Q_OBJECT
	public:
		DomainMiscView(QWidget* pParent = nullptr);
		~DomainMiscView();

	signals:
		void onAddClicked();
		void onImportClicked();
		void onBackClicked();
		void onRefreshPathView(const QString& path);
		void onPathViewClicked(const QString& path);

	private:
		void setupSignals();

	private:
		QPushButton* m_addButton;
		QPushButton* m_importButton;
		QPushButton* m_backButton;

		DomainPathView* m_pathView;
	};
}
