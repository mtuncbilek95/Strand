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

#include <Runtime/VirtualFile/VFSNode.h>

namespace Flax
{
	class ContentItemModel : public QAbstractItemModel
	{
		Q_OBJECT
	public:
		ContentItemModel(QObject* pParent = nullptr);
		~ContentItemModel();

		void setRootNode(const QString& path);

		QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
		QModelIndex parent(const QModelIndex& index) const override;
		int rowCount(const QModelIndex& parent = QModelIndex()) const override;
		int columnCount(const QModelIndex& parent = QModelIndex()) const override;
		bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
		QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
		QHash<int, QByteArray> roleNames() const override;
		Qt::ItemFlags flags(const QModelIndex& index) const override;

	private:
		VFSNode* m_rootNode;
	};
}
