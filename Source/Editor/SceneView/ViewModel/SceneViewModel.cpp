#include "SceneViewModel.h"

namespace Flax
{
	SceneViewModel::SceneViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
	}

	SceneViewModel::~SceneViewModel()
	{
	}

	struct SceneViewModelRegister
	{
		SceneViewModelRegister() { ViewModelRegistry::Get().RegisterVM<SceneViewModel>(); }
	};

	static SceneViewModelRegister gb_sceneViewModelRegister;
}
