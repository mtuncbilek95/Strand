#include "SceneGraphModel.h"

#include <Editor/SceneGraph/SceneGraphRole.h>

#include <Runtime/SceneGraph/Scene.h>
#include <Runtime/SceneGraph/Entity.h>

namespace Strand
{
	SceneGraphModel::SceneGraphModel(QObject* pParent) : QAbstractItemModel(pParent)
	{
	}

	void SceneGraphModel::addEntity(const QModelIndex& parent)
	{
		if (!parent.isValid())
		{
			i32 row = m_scene->GetCount();
			beginInsertRows(QModelIndex(), row, row);
			m_scene->AddChild("Entity_" + std::to_string(row));
			endInsertRows();
		}
		else
		{
			Entity* parentNode = static_cast<Entity*>(parent.internalPointer());
			i32 row = parentNode->GetCount();
			beginInsertRows(parent, row, row);
			parentNode->AddChild(parentNode->GetName() + "_Entity_" + std::to_string(row));
			endInsertRows();
		}
	}

	void SceneGraphModel::renameEntity(const QModelIndex& index, const QString& newName)
	{
		if (!index.isValid())
		{
			Log::Error(LogType::Editor, "Invalid index provided for renaming entity.");
			return;
		}
		Entity* entity = static_cast<Entity*>(index.internalPointer());
		if (!entity)
		{
			Log::Error(LogType::Editor, "Entity pointer is null while renaming.");
			return;
		}
		entity->SetName(newName.toStdString());
		dataChanged(index, index, { i32(SceneGraphRole::EntityName) });
	}

	void SceneGraphModel::duplicateEntity(const QModelIndex& index)
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void SceneGraphModel::removeEntity(const QModelIndex& index)
	{
		if (!index.isValid())
		{
			Log::Error(LogType::Editor, "Invalid index provided for removing entity.");
			return;
		}

		Entity* entity = static_cast<Entity*>(index.internalPointer());
		if (!entity)
		{
			Log::Error(LogType::Editor, "Entity pointer is null while removing.");
			return;
		}

		Entity* parent = entity->GetParent();
		if (parent)
		{
			beginRemoveRows(index.parent(), index.row(), index.row());
			parent->RemoveChild(entity->GetId());
			endRemoveRows();
		}
		else
		{
			beginRemoveRows(QModelIndex(), index.row(), index.row());
			m_scene->RemoveChild(entity->GetId());
			endRemoveRows();
		}
	}

	void SceneGraphModel::setCurrentScene(Scene* newScene)
	{
		if (newScene == m_scene)
		{
			Log::Warn(LogType::Editor, "Same scene is being tried to load. Retuning without process.");
			return;
		}

		if (!newScene)
		{
			Log::Error(LogType::Editor, "NewScene is null!");
			return;
		}

		beginResetModel();
		m_scene = newScene;
		endResetModel();
	}

	QModelIndex SceneGraphModel::indexOf(Entity* entity) const
	{
		if (!entity)
			return QModelIndex();

		Entity* parent = entity->GetParent();
		if (!parent)
		{
			for (usize i = 0; i < m_scene->GetCount(); ++i)
				if (m_scene->GetChild(i) == entity)
					return createIndex(i32(i), 0, entity);
		}
		else
		{
			for (usize i = 0; i < parent->GetCount(); ++i)
				if (parent->GetChild(i) == entity)
					return createIndex(i32(i), 0, entity);
		}

		return QModelIndex();
	}

	QModelIndex SceneGraphModel::index(int row, int column, const QModelIndex& parent) const
	{
		if (!m_scene)
			return QModelIndex();

		if (row < 0)
			return QModelIndex();

		Entity* mainNode = nullptr;

		if (!parent.isValid())
			mainNode = m_scene->GetChild(usize(row));
		else
		{
			Entity* parentNode = static_cast<Entity*>(parent.internalPointer());
			if (!parentNode)
				return QModelIndex();

			mainNode = parentNode->GetChild(usize(row));
		}

		if (!mainNode)
			return QModelIndex();

		return createIndex(row, column, mainNode);
	}

	QModelIndex SceneGraphModel::parent(const QModelIndex& index) const
	{
		if (!m_scene || !index.isValid())
			return QModelIndex();

		const Entity* ptr = static_cast<const Entity*>(index.internalPointer());
		if (!ptr)
			return QModelIndex();

		const Entity* parentPtr = ptr->GetParent();
		if (!parentPtr)
			return QModelIndex();

		const Entity* grandPtr = parentPtr->GetParent();
		if (grandPtr)
		{
			for (usize i = 0; i < grandPtr->GetCount(); ++i)
			{
				const Entity* child = grandPtr->GetChild(i);
				if (child == parentPtr)
					return createIndex(static_cast<i32>(i), 0, const_cast<Entity*>(parentPtr));
			}
		}
		else
		{
			for (usize i = 0; i < m_scene->GetCount(); ++i)
			{
				const Entity* child = m_scene->GetChild(i);
				if (child == parentPtr)
					return createIndex(static_cast<i32>(i), 0, const_cast<Entity*>(parentPtr));
			}
		}

		return QModelIndex();
	}

	int SceneGraphModel::rowCount(const QModelIndex& parent) const
	{
		if (!m_scene)
			return 0;

		if (!parent.isValid())
			return m_scene->GetCount();

		Entity* ptr = static_cast<Entity*>(parent.internalPointer());
		return ptr->GetCount();
	}

	int SceneGraphModel::columnCount(const QModelIndex& parent) const
	{
		return 1;
	}

	QVariant SceneGraphModel::data(const QModelIndex& index, int role) const
	{
		if (!m_scene)
			return QVariant();

		if (!index.isValid())
			return QVariant();

		switch (role)
		{
		case Qt::DisplayRole:
		case i32(SceneGraphRole::EntityName):
		{
			Entity* ptr = static_cast<Entity*>(index.internalPointer());
			return QString::fromStdString(ptr->GetName());
		}
		case i32(SceneGraphRole::EntityType):
			return "Entity";
		default:
			return QVariant();
		}

		return QVariant();
	}

	QVariant SceneGraphModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (!m_scene)
			return QVariant("Empty Scene");

		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return QString::fromStdString(m_scene->GetName());

		return QVariant();
	}

	Qt::ItemFlags SceneGraphModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
			return Qt::ItemIsDropEnabled;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable |
			Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable;
	}

	bool SceneGraphModel::setData(const QModelIndex& index, const QVariant& value, int role)
	{
		if (!index.isValid() || role != Qt::EditRole)
			return false;

		Entity* entity = static_cast<Entity*>(index.internalPointer());
		if (!entity)
			return false;

		entity->SetName(value.toString().toStdString());

		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
}