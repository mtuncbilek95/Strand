#include "ProjectBrowserViewModel.h"

#include <Runtime/FileSystem/VirtualNodeType.h>
#include <Runtime/FileSystem/IVirtualFileNode.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserModel.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserRole.h>
#include <Editor/ProjectBrowser/View/ProjectBrowserView.h>

namespace Flax
{
	ProjectBrowserViewModel::ProjectBrowserViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
	}

	ProjectBrowserViewModel::~ProjectBrowserViewModel()
	{
	}

	void ProjectBrowserViewModel::onItemSelected(const QModelIndex& index)
	{
	}

	void ProjectBrowserViewModel::onItemDoubleClicked(const QModelIndex& index)
	{
		VirtualNodeType type = VirtualNodeType(index.data(i32(ProjectBrowserRole::ObjectType)).toInt());
		if (type == VirtualNodeType::Folder)
		{
			IVirtualFileNode* node = m_model->Node(index);
			emit setCurrentIndex(index);
		}
		else
			return;
	}

	void ProjectBrowserViewModel::onItemContextMenuRequested(const QModelIndex& index)
	{
	}

	struct ProjectBrowserRegister
	{
		ProjectBrowserRegister() { ViewModelRegistry::Get().RegisterVM<ProjectBrowserViewModel>(); }
	};
	static ProjectBrowserRegister gb_projectBrowserViewModel;
}
