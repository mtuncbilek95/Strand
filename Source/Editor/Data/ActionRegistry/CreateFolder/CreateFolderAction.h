/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class CreateFolderAction : public QAction
	{
		Q_OBJECT
	public:
		CreateFolderAction(const QString& text, QObject* pParent = nullptr);
		~CreateFolderAction();

	signals:
		void onTriggered(b8 checked = false);

	public slots:
		void onCreateFolder(const QModelIndex& index);

	private:
	};
}
