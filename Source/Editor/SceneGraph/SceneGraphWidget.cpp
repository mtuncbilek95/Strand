#include "SceneGraphWidget.h"

#include <Editor/SceneGraph/SceneGraphModel.h>
#include <Editor/SceneGraph/SceneGraphTreeView.h>


namespace Flax
{
	SceneGraphWidget::SceneGraphWidget(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("Scene_HierarchyWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);

		m_sgModel = new SceneGraphModel(this);
		m_sgModel->setCurrentScene(nullptr);
		m_treeView = new SceneGraphTreeView(this);
		m_treeView->setModel(m_sgModel);

		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		mainLayout->addWidget(m_treeView);
	}

	SceneGraphWidget::~SceneGraphWidget()
	{
	}
}
