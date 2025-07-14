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
	class IVirtualFileNode;
	class IVirtualFileSystem;
	class IFileStream;

	class ProjectBrowserModel : public QAbstractItemModel
	{
		Q_OBJECT
	public:
		ProjectBrowserModel(QObject* pParent = nullptr);
		~ProjectBrowserModel();

		IVirtualFileNode* Root();
		IVirtualFileNode* Node(const QModelIndex& index);

		QModelIndex index(int row, int column, const QModelIndex& parent) const override final;
		QModelIndex parent(const QModelIndex& index) const override final;
		int rowCount(const QModelIndex& parent) const override final;
		int columnCount(const QModelIndex& parent) const override final;
		QVariant data(const QModelIndex& index, int role) const override final;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override final;
		Qt::ItemFlags flags(const QModelIndex& index) const override final;
		bool setData(const QModelIndex& index, const QVariant& value, int role) override final;
		QModelIndex rootIndex() const;

	private:
		IVirtualFileNode* getNode(const QModelIndex& index) const;

	private:
		Ref<IVirtualFileNode> m_rootNode;
		Ref<IVirtualFileSystem> m_fileSystem;
	};
}
