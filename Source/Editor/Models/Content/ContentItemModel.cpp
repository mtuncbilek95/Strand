#include "ContentItemModel.h"

#include <Runtime/Resources/Asset/Core/AssetMetadata.h>
#include <Runtime/VirtualFile/Service/VFSService.h>

namespace Flax
{
	ContentItemModel::ContentItemModel(QObject* pParent) : QAbstractItemModel(pParent)
	{
	}

	ContentItemModel::~ContentItemModel()
	{
	}

    void ContentItemModel::setRootNode(const QString& path)
    {

    }

	QModelIndex ContentItemModel::index(int row, int column, const QModelIndex& parent) const
	{
		return QModelIndex();
	}

	QModelIndex ContentItemModel::parent(const QModelIndex& index) const
	{
		return QModelIndex();
	}

	int ContentItemModel::rowCount(const QModelIndex& parent) const
	{
		return 0;
	}

	int ContentItemModel::columnCount(const QModelIndex& parent) const
	{
		return 1;
	}

	bool ContentItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
	{
		return false;
	}

	QVariant ContentItemModel::data(const QModelIndex& index, int role) const
	{
		return QVariant();
	}

	QHash<int, QByteArray> ContentItemModel::roleNames() const
	{
		QHash<int, QByteArray> roles;
		roles[Qt::DisplayRole] = "display";
		return roles;
	}

	Qt::ItemFlags ContentItemModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
			return Qt::NoItemFlags;

		VFSNode* node = static_cast<VFSNode*>(index.internalPointer());
		if (node->Name().ends_with(".meta") || node->Name().ends_with(".fasset"))
			return Qt::ItemIsSelectable;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
}
