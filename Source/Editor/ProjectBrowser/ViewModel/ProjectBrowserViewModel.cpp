#include "ProjectBrowserViewModel.h"

namespace Flax
{
	ProjectBrowserViewModel::ProjectBrowserViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
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
