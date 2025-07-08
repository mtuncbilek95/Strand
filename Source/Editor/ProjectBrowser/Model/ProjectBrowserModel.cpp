#include "ProjectBrowserModel.h"

namespace Flax
{
	ProjectBrowserModel::ProjectBrowserModel(QObject* pParent)
	{
	}

	ProjectBrowserModel::~ProjectBrowserModel()
	{
	}

	QModelIndex ProjectBrowserModel::index(int row, int column, const QModelIndex& parent) const
	{
		return QModelIndex();
	}

	QModelIndex ProjectBrowserModel::parent(const QModelIndex& index) const
	{
		return QModelIndex();
	}

	int ProjectBrowserModel::rowCount(const QModelIndex& parent) const
	{
		return 0;
	}

	int ProjectBrowserModel::columnCount(const QModelIndex& parent) const
	{
		return 0;
	}

	QVariant ProjectBrowserModel::data(const QModelIndex& index, int role) const
	{
		return QVariant();
	}

	QVariant ProjectBrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		return QVariant();
	}

	Qt::ItemFlags ProjectBrowserModel::flags(const QModelIndex& index) const
	{
		return Qt::ItemFlags();
	}

	bool ProjectBrowserModel::setData(const QModelIndex& index, const QVariant& value, int role)
	{
		return false;
	}
}
