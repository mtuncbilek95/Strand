#include "HierarchyItemModel.h"

#include <Runtime/Scene/Scene.h>
#include <Runtime/Scene/Entity.h>

namespace Flax
{
	HierarchyItemModel::HierarchyItemModel(QObject* pParent) : QAbstractItemModel(pParent)
	{
	}

	HierarchyItemModel::~HierarchyItemModel()
	{
	}

	void HierarchyItemModel::addEntity(const QModelIndex& parent)
	{
		beginResetModel();

		if (!parent.isValid())
			m_currentScene->AddEntity(nullptr);
		else
			static_cast<Entity*>(parent.internalPointer())->AddChild();

		endResetModel();
	}

	void HierarchyItemModel::removeEntity(const QModelIndex& index)
	{
	}

	void HierarchyItemModel::setCurrentScene(Scene* newScene)
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

	QModelIndex HierarchyItemModel::index(int row, int column, const QModelIndex& parent) const
	{
		// If has no proper index return invalid QModelIndex()
		if (!hasIndex(row, column, parent))
			return QModelIndex();

		// If parent is not valid, return it from root
		if (!parent.isValid())
			return createIndex(row, column, m_currentScene->Child(usize(row)));

		// Parent is valid. Turn into Entity* then use row to create correct QModelIndex()
		Entity* parentPtr = static_cast<Entity*>(parent.internalPointer());
		return createIndex(row, column, parentPtr->Child(usize(row)));
	}

	QModelIndex HierarchyItemModel::parent(const QModelIndex& index) const
	{
		if (!index.isValid())
			return QModelIndex();

		if (index.parent().isValid())
		{
			Entity* parentPtr = static_cast<Entity*>(index.parent().internalPointer());
			Entity* grandPtr = parentPtr->Parent();

			if (grandPtr)
			{
				for (usize i = 0; i < grandPtr->Count(); i++)
				{
					if (grandPtr->Child(i) == parentPtr)
						return createIndex(i, 0, parentPtr);
				}

				return QModelIndex();
			}
		}

		return QModelIndex();
	}

	int HierarchyItemModel::rowCount(const QModelIndex& parent) const
	{
		if (!parent.isValid())
			return m_currentScene->Count();

		Entity* ptr = static_cast<Entity*>(parent.internalPointer());
		return ptr->Count();
	}

	int HierarchyItemModel::columnCount(const QModelIndex& parent) const
	{
		return 0;
	}

	QVariant HierarchyItemModel::data(const QModelIndex& index, int role) const
	{
		return QVariant();
	}
}
