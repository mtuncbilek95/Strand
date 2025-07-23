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
	class Scene;
	class Entity;

	class SceneGraphModel : public QAbstractItemModel
	{
		Q_OBJECT
	public:
		SceneGraphModel(QObject* pParent = nullptr);
		~SceneGraphModel();

		void addEntity(const QModelIndex& parent);
		void renameEntity(const QModelIndex& index, const QString& newName);
		void duplicateEntity(const QModelIndex& index);
		void removeEntity(const QModelIndex& index);
		void setCurrentScene(Scene* newScene);

		QModelIndex indexOf(Entity* entity) const;

		QModelIndex index(int row, int column, const QModelIndex& parent) const override final;
		QModelIndex parent(const QModelIndex& index) const override final;
		int rowCount(const QModelIndex& parent) const override final;
		int columnCount(const QModelIndex& parent) const override final;
		QVariant data(const QModelIndex& index, int role) const override final;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override final;
		Qt::ItemFlags flags(const QModelIndex& index) const override final;
		bool setData(const QModelIndex& index, const QVariant& value, int role) override final;

	private:
		Scene* m_currentScene;
	};
}