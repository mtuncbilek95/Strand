#include "SceneGraphModel.h"

#include <Editor/SceneGraph/SceneGraphRole.h>

namespace Flax
{
	SceneGraphModel::SceneGraphModel(QObject* pParent) : QAbstractItemModel(pParent)
	{
	}

	SceneGraphModel::~SceneGraphModel()
	{
	}

	void SceneGraphModel::addEntity(const QModelIndex& parent)
	{
		EDITOR_NOT_IMPLEMENTED_YET();
	}

	void SceneGraphModel::renameEntity(const QModelIndex& index, const QString& newName)
	{
		EDITOR_NOT_IMPLEMENTED_YET();
	}

	void SceneGraphModel::duplicateEntity(const QModelIndex& index)
	{
		EDITOR_NOT_IMPLEMENTED_YET();
	}

	void SceneGraphModel::removeEntity(const QModelIndex& index)
	{
		EDITOR_NOT_IMPLEMENTED_YET();
	}

	void SceneGraphModel::setCurrentScene(Scene* newScene)
	{
		EDITOR_NOT_IMPLEMENTED_YET();
	}

	QModelIndex SceneGraphModel::indexOf(Entity* entity) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(QModelIndex());
	}

	QModelIndex SceneGraphModel::index(int row, int column, const QModelIndex& parent) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(QModelIndex());
	}

	QModelIndex SceneGraphModel::parent(const QModelIndex& index) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(QModelIndex());
	}

	int SceneGraphModel::rowCount(const QModelIndex& parent) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(0);
	}

	int SceneGraphModel::columnCount(const QModelIndex& parent) const
	{
		return 1;
	}

	QVariant SceneGraphModel::data(const QModelIndex& index, int role) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(QVariant());
	}

	QVariant SceneGraphModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		EDITOR_NOT_IMPLEMENTED_YET(QVariant());
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
		EDITOR_NOT_IMPLEMENTED_YET(false);
	}
}