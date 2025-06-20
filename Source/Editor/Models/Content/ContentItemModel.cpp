#include "ContentItemModel.h"

#include <Runtime/Resources/Asset/Core/AssetMetadata.h>

namespace Flax
{
	ContentItemModel::ContentItemModel(QObject* pParent) : QAbstractItemModel(pParent)
	{
	}

	ContentItemModel::~ContentItemModel()
	{
	}

	QModelIndex ContentItemModel::index(int row, int column, const QModelIndex& parent) const
	{
		// If there is no index
		if (!hasIndex(row, column, parent))
			return QModelIndex();

		VFSNode* parentNode = nullptr;

		// If parent is invalid
		if (!parent.isValid())
			parentNode = m_rootNode.get();
		else
			parentNode = static_cast<VFSNode*>(parent.internalPointer());

		// If parent node is nullptr
		if (!parentNode)
			return QModelIndex();

		const auto& children = parentNode->Children();
		if (row < 0 || row >= static_cast<i32>(children.size()))
			return QModelIndex();

		return createIndex(row, column, children[row]);
	}

	QModelIndex ContentItemModel::parent(const QModelIndex& index) const
	{
		if (!index.isValid())
			return QModelIndex();

		// Get the node represented by this index
		VFSNode* childNode = static_cast<VFSNode*>(index.internalPointer());
		if (!childNode)
			return QModelIndex();

		// Get the parent node
		VFSNode* parentNode = childNode->Owner();
		if (!parentNode || parentNode == m_rootNode.get())
			return QModelIndex(); // Root-level nodes return invalid parent

		// Find the parent's index (row) within its own parent
		VFSNode* parentOfParent = parentNode->Owner();
		if (!parentOfParent)
			return QModelIndex(); // Safety check

		const auto& siblings = parentOfParent->Children();
		i32 row = -1;

		for (usize i = 0; i < siblings.size(); ++i)
		{
			if (siblings[i] == parentNode)
			{
				row = static_cast<i32>(i);
				break;
			}
		}

		if (row == -1)
			return QModelIndex(); // Should not happen unless tree is corrupted

		// Return QModelIndex for the parent node
		return createIndex(row, 0, parentNode);
	}

	int ContentItemModel::rowCount(const QModelIndex& parent) const
	{
		if (!m_rootNode)
			return 0;

		VFSNode* node = nullptr;

		// If parent is invalid
		if (!parent.isValid())
			node = m_rootNode.get();
		else // If it's valid
			node = static_cast<VFSNode*>(parent.internalPointer());

		// But if node is invalid
		if (!node)
			return 0;

		return static_cast<int>(node->Children().size());
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
		if (!index.isValid())
			return QVariant();

		VFSNode* node = static_cast<VFSNode*>(index.internalPointer());

		if (!node)
			return QVariant();

		switch (role)
		{
		case Qt::DisplayRole:
		{
			String onlyName = StringHelpers::StripExtension(node->Name());
			return QString::fromStdString(onlyName);
		}
		case Qt::DecorationRole:
		{
			if (node->Type() == VFSNodeType::Directory)
				return QIcon(":/Icons/Shared/Folder.svg");
			else if (node->Type() == VFSNodeType::File)
			{
				AssetMetadata* meta = nullptr;

				if (!meta)
					return QIcon(":/Icons/Shared/File.svg");

				if (meta->AssetType() == "texture")
					return QIcon(":/Icons/Shared/Image.svg");

				if (meta->AssetType() == "script")
					return QIcon(":/Icons/Shared/Script.svg");

				if (meta->AssetType() == "shader")
					return QIcon(":/Icons/Shared/Shader.svg");

				if (meta->AssetType() == "material")
					return QIcon(":/Icons/Shared/Material.svg");

				if (meta->AssetType() == "renderGraph")
					return QIcon(":/Icons/Shared/RenderGraph.svg");

				return QIcon(":/Icons/Shared/File.svg");
			}
			else if (node->Type() == VFSNodeType::Unknown)
				return QIcon(":/Icons/Shared/Unknown.svg");
		}
		}

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
		if (node->Name().ends_with(".meta") || node->Name().ends_with(".asset"))
			return Qt::ItemIsSelectable;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
}
