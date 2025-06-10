#include "HierarchyWidget.h"

#include <Editor/Models/Hierarchy/HierarchyItemModel.h>

namespace Flax
{
	HierarchyWidget::HierarchyWidget(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("Scene_HierarchyWidget");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setContentsMargins(0, 0, 0, 0);
		
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		m_model = new HierarchyItemModel(this);
		m_view = new QTreeView(this);
		m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_view->viewport()->installEventFilter(this);
		m_view->setObjectName("Scene_HierarchyWidget_TreeView");
		m_view->setContextMenuPolicy(Qt::CustomContextMenu);
		m_view->setModel(m_model);

		mainLayout->addWidget(m_view);

		connect(m_view, &QTreeView::clicked, this, &HierarchyWidget::onItemSelected);
		connect(m_view, &QTreeView::customContextMenuRequested, this, &HierarchyWidget::onContextMenuRequested);
		connect(m_view, &QTreeView::doubleClicked, this, &HierarchyWidget::onItemDoubleClicked);
	}

	HierarchyWidget::~HierarchyWidget()
	{
	}

	bool HierarchyWidget::eventFilter(QObject* pWatched, QEvent* pEvent)
	{
		if ((pWatched == m_view || pWatched == m_view->viewport()) && pEvent->type() == QEvent::MouseButtonPress)
		{
			auto* mouseEvent = static_cast<QMouseEvent*>(pEvent);
			if (mouseEvent->button() == Qt::LeftButton)
			{
				QModelIndex index = m_view->indexAt(mouseEvent->pos());
				if (!index.isValid())
				{
					m_view->clearSelection();
					m_view->setCurrentIndex(QModelIndex());
				}
			}
		}
		return QWidget::eventFilter(pWatched, pEvent);
	}

	void HierarchyWidget::onItemSelected(const QModelIndex& index)
	{

	}

	void HierarchyWidget::onContextMenuRequested(const QPoint& pos)
	{
		QModelIndex index = m_view->indexAt(pos);

		QMenu contextMenu;
		QAction* addEntityAction = nullptr;
		QAction* renameEntityAction = nullptr;
		QAction* duplicateEntityAction = nullptr;
		QAction* removeEntityAction = nullptr;

		if (index.isValid())
		{
			addEntityAction = contextMenu.addAction("Add Child Entity");
			renameEntityAction = contextMenu.addAction("Rename");
			duplicateEntityAction = contextMenu.addAction("Duplicate");
			removeEntityAction = contextMenu.addAction("Remove");
		}
		else
		{
			addEntityAction = contextMenu.addAction("Add Entity");
			m_view->clearSelection();
		}

		QAction* selectedAction = contextMenu.exec(m_view->viewport()->mapToGlobal(pos));
		if (!selectedAction)
			return;

		if (selectedAction == addEntityAction)
			m_model->addEntity(index);
		else if (removeEntityAction && selectedAction == removeEntityAction)
			m_model->removeEntity(index);
		else if (renameEntityAction && selectedAction == renameEntityAction)
			m_view->edit(index);
		else if (duplicateEntityAction && selectedAction == duplicateEntityAction)
			m_model->duplicateEntity(index);
		else
			return; // No action handled
	}

	void HierarchyWidget::onItemDoubleClicked(const QModelIndex& index)
	{
	}
}
