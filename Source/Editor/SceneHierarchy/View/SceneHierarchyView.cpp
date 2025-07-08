#include "SceneHierarchyView.h"

#include <Editor/SceneHierarchy/Model/SceneHierarchyModel.h>
#include <Editor/SceneHierarchy/ViewModel/SceneHierarchyViewModel.h>

namespace Flax
{
	SceneHierarchyView::SceneHierarchyView(QWidget* pParent) : QWidget(pParent)
	{
		m_viewModel = ViewModelRegistry::Get().ViewModel<SceneHierarchyViewModel>().get();

		setObjectName("Scene_HierarchyWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);

		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		m_view = new QTreeView(this);
		m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		//m_view->viewport()->installEventFilter(service);
		m_view->setObjectName("Scene_HierarchyWidget_TreeView");
		m_view->setContextMenuPolicy(Qt::CustomContextMenu);
		m_view->setModel(m_viewModel->Model());

		mainLayout->addWidget(m_view);

		//connect(m_view, &QTreeView::clicked, service, &HierarchyService::onItemSelected);
		//connect(m_view, &QTreeView::customContextMenuRequested, service, &HierarchyService::onContextMenuRequested);
		//connect(m_view, &QTreeView::doubleClicked, service, &HierarchyService::onItemDoubleClicked);
	}

	SceneHierarchyView::~SceneHierarchyView()
	{
	}
}