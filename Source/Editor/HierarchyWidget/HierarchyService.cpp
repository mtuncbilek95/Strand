#include "HierarchyService.h"

#include <Editor/Data/Service/UIService.h>
#include <Editor/Models/Hierarchy/HierarchyItemModel.h>
#include <Editor/HierarchyWidget/HierarchyWidget.h>

#include <Runtime/Scene/Scene.h>

namespace Flax
{
	namespace
	{
		struct HierarchyServiceRegister
		{
			HierarchyServiceRegister()
			{
				UIService::Register<HierarchyService>(new HierarchyService());
			}
		};

		static HierarchyServiceRegister gbHierarchyService;
	}

	HierarchyService::HierarchyService(QObject* parent)
	{
		m_hModel = NewRef<HierarchyItemModel>(this);
		m_hModel->setCurrentScene(new Scene("DumpScene"));
	}

	bool HierarchyService::eventFilter(QObject* pWatched, QEvent* pEvent)
	{
		if ((pWatched == m_hWidget->View() || pWatched == m_hWidget->View()->viewport()) && pEvent->type() == QEvent::MouseButtonPress)
		{
			auto* mouseEvent = static_cast<QMouseEvent*>(pEvent);
			if (mouseEvent->button() == Qt::LeftButton)
			{
				QModelIndex index = m_hWidget->View()->indexAt(mouseEvent->pos());
				if (!index.isValid())
				{
					m_hWidget->View()->clearSelection();
					m_hWidget->View()->setCurrentIndex(QModelIndex());
				}
			}
		}
		return QObject::eventFilter(pWatched, pEvent);
	}

	void HierarchyService::onItemSelected(const QModelIndex& index)
	{

	}

	void HierarchyService::onContextMenuRequested(const QPoint& pos)
	{
		QModelIndex index = m_hWidget->View()->indexAt(pos);

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
			m_hWidget->View()->clearSelection();
		}

		QAction* selectedAction = contextMenu.exec(m_hWidget->View()->viewport()->mapToGlobal(pos));
		if (!selectedAction)
			return;

		if (selectedAction == addEntityAction)
			m_hModel->addEntity(index);
		else if (removeEntityAction && selectedAction == removeEntityAction)
			m_hModel->removeEntity(index);
		else if (renameEntityAction && selectedAction == renameEntityAction)
			m_hWidget->View()->edit(index);
		else if (duplicateEntityAction && selectedAction == duplicateEntityAction)
			m_hModel->duplicateEntity(index);
		else
			return; // No action handled
	}

	void HierarchyService::onItemDoubleClicked(const QModelIndex& index)
	{
	}
}
