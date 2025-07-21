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
