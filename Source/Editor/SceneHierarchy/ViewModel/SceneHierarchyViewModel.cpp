#include "SceneHierarchyViewModel.h"

#include <Editor/SceneHierarchy/Model/SceneHierarchyModel.h>
#include <Runtime/Scene/Scene.h>

namespace Flax
{
	SceneHierarchyViewModel::SceneHierarchyViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
		m_model = new SceneHierarchyModel(this);
	}

	SceneHierarchyViewModel::~SceneHierarchyViewModel()
	{
	}

	void SceneHierarchyViewModel::SetScene(Scene* scene)
	{
		if (scene == nullptr)
			scene = new Scene();

		m_model->setCurrentScene(scene);
	}

	void SceneHierarchyViewModel::onContextMenuRequested(const QPoint& pos)
	{
	}

	struct SceneHierarchyRegister
	{
		SceneHierarchyRegister() { ViewModelRegistry::Get().RegisterVM<SceneHierarchyViewModel>(); }
	};
	static SceneHierarchyRegister gb_sceneHierarchyViewModel;
}
