#include "ProjectBrowserViewModel.h"

#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserIconProvider.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserFilterProxy.h>

namespace Flax
{
	ProjectBrowserViewModel::ProjectBrowserViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
		m_iconProvider = new ProjectBrowserIconProvider();
		m_proxy = new ProjectBrowserFilterProxy(this);
		m_fileModel = new QFileSystemModel(this);

		m_proxy->setSourceModel(m_fileModel);

		m_fileModel->setReadOnly(true);
		m_fileModel->setIconProvider(m_iconProvider);
	}

	ProjectBrowserViewModel::~ProjectBrowserViewModel()
	{
	}

	struct ProjectBrowserRegister
	{
		ProjectBrowserRegister() { ViewModelRegistry::Get().RegisterVM<ProjectBrowserViewModel>(); }
	};
	static ProjectBrowserRegister gb_projectBrowserViewModel;
}
