#include "ProjectBrowserModel.h"

#include <Runtime/FileSystem/IVirtualFileNode.h>
#include <Runtime/FileSystem/IVirtualFileSystem.h>
#include <Runtime/FileSystem/Service/VirtualFileService.h>

#include <Editor/ProjectBrowser/Model/ProjectBrowserRole.h>

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
	ProjectBrowserModel::ProjectBrowserModel(QObject* pParent) : QAbstractItemModel(pParent)
		, m_rootNode(nullptr), m_fileSystem(nullptr)
	{
		auto vfm = RuntimeService::Get<VirtualFileService>();
		m_rootNode = vfm->RootNode("Assets");
		if (!m_rootNode)
		{
			Log::Error(LogType::FileSystem, "Failed to get root node for Project Browser Model.");
			return;
		}

		m_fileSystem = vfm->FileSystem("Assets");
		if (!m_fileSystem)
		{
			Log::Error(LogType::FileSystem, "Failed to get file system for Project Browser Model.");
			return;
		}
	}

	ProjectBrowserModel::~ProjectBrowserModel()
	{
	}

	void ProjectBrowserModel::ResetModel(const QModelIndex& index)
	{
		QModelIndex targetIdx = index.isValid() ? index : rootIndex();
		beginResetModel();
		IVirtualFileNode* node = getNode(targetIdx);
		node->Refresh();
		endResetModel();
	}

	IVirtualFileNode* ProjectBrowserModel::Root()
	{
		beginResetModel();
		m_rootNode->Refresh();
		endResetModel();

		return m_rootNode.get();
	}

	IVirtualFileNode* ProjectBrowserModel::Node(const QModelIndex& index)
	{
		if(index.isValid())
		{
			beginResetModel();
			IVirtualFileNode* node = getNode(index);

			if (node)
			{
				node->Refresh();
				endResetModel();
				return node;
			}
		}

		return nullptr;
	}

	QModelIndex ProjectBrowserModel::index(int row, int column, const QModelIndex& parent) const
	{
		if (!hasIndex(row, column, parent))
			return QModelIndex();

		IVirtualFileNode* parentNode = nullptr;
		if (!parent.isValid())
			parentNode = m_rootNode.get();
		else
			parentNode = getNode(parent);

		if (parentNode && parentNode->IsFolder())
		{
			Ref<IVirtualFileNode> childNode = parentNode->Child(usize(row));
			if (childNode) 
				return createIndex(row, column, childNode.get());
		}

		return QModelIndex();
	}

	QModelIndex ProjectBrowserModel::parent(const QModelIndex& index) const
	{
		if (!index.isValid())
			return QModelIndex();

		IVirtualFileNode* childNode = getNode(index);
		if (!childNode)
			return QModelIndex();

		IVirtualFileNode* parentNode = childNode->Parent();
		if (!parentNode || parentNode == m_rootNode.get())
			return QModelIndex();

		return createIndex(parentNode->Index(), 0, parentNode);
	}

	int ProjectBrowserModel::rowCount(const QModelIndex& parent) const
	{
		IVirtualFileNode* parentNode = nullptr;
		if (!parent.isValid())
			parentNode = m_rootNode.get();
		else
			parentNode = getNode(parent);

		if (parentNode && parentNode->IsFolder())
			return i32(parentNode->Count());

		return 0;
	}

	int ProjectBrowserModel::columnCount(const QModelIndex& parent) const
	{
		return 1;
	}

	QVariant ProjectBrowserModel::data(const QModelIndex& index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		IVirtualFileNode* node = getNode(index);
		if (!node)
			return QVariant();

		switch (role)
		{
		case Qt::DisplayRole:
		case i32(ProjectBrowserRole::ObjectName):
			return QString::fromStdString(node->Name());
		case i32(ProjectBrowserRole::ObjectType):
			return i32(node->Type());
		case i32(ProjectBrowserRole::ObjectPath):
			return QString::fromStdString(node->VirtualPath().string());
		case Qt::DecorationRole:
			return node->Type() == VirtualNodeType::Folder ? 
				QIcon(":/Icons/ContentBrowser/PB_Folder.svg") :
				QIcon(":/Icons/ContentBrowser/PB_File.svg");
		default:
			return QVariant();
		}

		return QVariant();
	}

	QVariant ProjectBrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		return QVariant();
	}

	Qt::ItemFlags ProjectBrowserModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
			return Qt::NoItemFlags;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	bool ProjectBrowserModel::setData(const QModelIndex& index, const QVariant& value, int role)
	{
		return false;
	}

	QModelIndex ProjectBrowserModel::rootIndex() const
	{
		return createIndex(0, 0, m_rootNode.get());
	}

	IVirtualFileNode* ProjectBrowserModel::getNode(const QModelIndex& index) const
	{
		if (index.isValid())
			return static_cast<IVirtualFileNode*>(index.internalPointer());

		return nullptr;
	}
}
