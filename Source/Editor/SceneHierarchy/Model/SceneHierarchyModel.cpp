#include "SceneHierarchyModel.h"

#include <Editor/SceneHierarchy/Model/SceneHierarchyCustomRole.h>

#include <Engine/Scene/Scene.h>
#include <Engine/Scene/Entity.h>

namespace Flax
{
	SceneHierarchyModel::SceneHierarchyModel(QObject* pParent) : QAbstractItemModel(pParent),
		m_currentScene(nullptr)
	{
	}

	SceneHierarchyModel::~SceneHierarchyModel()
	{
	}

	void SceneHierarchyModel::addEntity(const QModelIndex& parent)
	{
		Entity* parentEntity = parent.isValid()
			? static_cast<Entity*>(parent.internalPointer())
			: m_currentScene->Root();

		i32 row = static_cast<i32>(parentEntity->Count());

		beginInsertRows(parent, row, row);
		parentEntity->AddChild();
		endInsertRows();
	}

	void SceneHierarchyModel::renameEntity(const QModelIndex& index, const QString& newName)
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
		dataChanged(index, index, { i32(SceneHierarchyCustomRole::EntityName) });
	}

	void SceneHierarchyModel::duplicateEntity(const QModelIndex& index)
	{
	}

	void SceneHierarchyModel::removeEntity(const QModelIndex& index)
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

		Entity* parent = entity->Parent();
		if (parent)
		{
			beginRemoveRows(index.parent(), index.row(), index.row());
			parent->RemoveChild(entity);
			endRemoveRows();
		}
		else
		{
			beginRemoveRows(QModelIndex(), index.row(), index.row());
			m_currentScene->RemoveEntity(entity);
			endRemoveRows();
		}
	}

	void SceneHierarchyModel::setCurrentScene(Scene* newScene)
	{
		if (newScene == m_currentScene)
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
		m_currentScene = newScene;
		endResetModel();
	}

	QModelIndex SceneHierarchyModel::indexOf(Entity* entity) const
	{
		if (!entity)
			return QModelIndex();

		Entity* parent = entity->Parent();
		if (!parent)
		{
			for (int i = 0; i < m_currentScene->Count(); ++i)
				if (m_currentScene->Child(i) == entity)
					return index(i, 0, QModelIndex());
		}
		else
		{
			for (int i = 0; i < parent->Count(); ++i)
				if (parent->Child(i) == entity)
					return index(i, 0, createIndex(0, 0, parent));
		}

		return QModelIndex();
	}

	QModelIndex SceneHierarchyModel::index(int row, int column, const QModelIndex& parent) const
	{
		if (!m_currentScene)
			return QModelIndex();

		if (!hasIndex(row, column, parent))
			return QModelIndex();

		Entity* child = nullptr;

		if (!parent.isValid())
			child = m_currentScene->Child(static_cast<usize>(row));
		else
		{
			const Entity* parentPtr = static_cast<const Entity*>(parent.internalPointer());
			if (!parentPtr)
				return QModelIndex();

			child = parentPtr->Child(static_cast<usize>(row));
		}

		if (!child)
			return QModelIndex();

		return createIndex(row, column, child);
	}

	QModelIndex SceneHierarchyModel::parent(const QModelIndex& index) const
	{
		if (!m_currentScene || !index.isValid())
			return QModelIndex();

		const Entity* ptr = static_cast<const Entity*>(index.internalPointer());
		if (!ptr)
			return QModelIndex();

		const Entity* parentPtr = ptr->Parent();
		if (!parentPtr)
			return QModelIndex();

		const Entity* grandPtr = parentPtr->Parent();
		if (grandPtr)
		{
			for (usize i = 0; i < grandPtr->Count(); ++i)
			{
				const Entity* child = grandPtr->Child(i);
				if (child == parentPtr)
					return createIndex(static_cast<i32>(i), 0, const_cast<Entity*>(parentPtr));
			}
		}
		else
		{
			for (usize i = 0; i < m_currentScene->Count(); ++i)
			{
				const Entity* child = m_currentScene->Child(i);
				if (child == parentPtr)
					return createIndex(static_cast<i32>(i), 0, const_cast<Entity*>(parentPtr));
			}
		}

		return QModelIndex();
	}

	int SceneHierarchyModel::rowCount(const QModelIndex& parent) const
	{
		if (!m_currentScene)
			return 0;

		if (!parent.isValid())
			return m_currentScene->Count();

		Entity* ptr = static_cast<Entity*>(parent.internalPointer());
		return ptr->Count();
	}

	int SceneHierarchyModel::columnCount(const QModelIndex& parent) const
	{
		return 1;
	}

	QVariant SceneHierarchyModel::data(const QModelIndex& index, int role) const
	{
		if (!m_currentScene)
			return QVariant();

		if (!index.isValid())
			return QVariant();

		switch (role)
		{
		case Qt::DisplayRole:
		case i32(SceneHierarchyCustomRole::EntityName):
		{
			Entity* ptr = static_cast<Entity*>(index.internalPointer());
			return QString::fromStdString(ptr->Name());
		}
		case i32(SceneHierarchyCustomRole::EntityType):
			return "Entity";
		default:
			return QVariant();
		}

		return QVariant();
	}

	QVariant SceneHierarchyModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (!m_currentScene)
			return QVariant("Empty Scene");

		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return QString::fromStdString(m_currentScene->Name());

		return QVariant();
	}

	Qt::ItemFlags SceneHierarchyModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
			return Qt::ItemIsDropEnabled;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable |
			Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable;
	}

	bool SceneHierarchyModel::setData(const QModelIndex& index, const QVariant& value, int role)
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