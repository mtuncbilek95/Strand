#include "HierarchyWidget.h"

#include <Editor/Models/Hierarchy/HierarchyItemModel.h>
#include <Editor/HierarchyWidget/HierarchyService.h>

namespace Flax
{
	HierarchyWidget::HierarchyWidget(QWidget* pParent) : QWidget(pParent)
	{
		auto* service = UIService::Get<HierarchyService>();

		setObjectName("Scene_HierarchyWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);
		
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		service->setWidget(this);
		m_view = new QTreeView(this);
		m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_view->viewport()->installEventFilter(service);
		m_view->setObjectName("Scene_HierarchyWidget_TreeView");
		m_view->setContextMenuPolicy(Qt::CustomContextMenu);
		m_view->setModel(service->Model());

		mainLayout->addWidget(m_view);

		connect(m_view, &QTreeView::clicked, service, &HierarchyService::onItemSelected);
		connect(m_view, &QTreeView::customContextMenuRequested, service, &HierarchyService::onContextMenuRequested);
		connect(m_view, &QTreeView::doubleClicked, service, &HierarchyService::onItemDoubleClicked);
	}

	HierarchyWidget::~HierarchyWidget()
	{
	}
}
