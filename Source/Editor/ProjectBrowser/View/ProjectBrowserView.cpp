#include "ProjectBrowserView.h"

#include <Editor/ProjectBrowser/Model/ProjectBrowserModel.h>
#include <Editor/ProjectBrowser/View/ProjectBreadcrumbsView.h>
#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserViewModel.h>

namespace Flax
{
	ProjectBrowserView::ProjectBrowserView(QWidget* pParent) : QWidget(pParent)
	{
		m_viewModel = ViewModelRegistry::Get().ViewModel<ProjectBrowserViewModel>().get();
		m_viewModel->SetModel(new ProjectBrowserModel(m_viewModel));
		m_breadcrumbs = new ProjectBreadcrumbsView(this);

		m_listView = new QListView(this);

		m_listView->setModel(m_viewModel->Model());
		m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
		m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_listView->setViewMode(QListView::IconMode);
		m_listView->setUniformItemSizes(true);

		m_listView->setIconSize(QSize(96, 96));
		m_listView->setGridSize(QSize(128, 128));
		m_listView->setSpacing(12);
		m_listView->setResizeMode(QListView::Adjust);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addWidget(m_breadcrumbs);
		layout->addWidget(m_listView);
		layout->setStretch(0, 1);
		layout->setStretch(1, 4);

		connect(m_listView, &QListView::activated, m_viewModel, &ProjectBrowserViewModel::onItemDoubleClicked);
		connect(m_viewModel, &ProjectBrowserViewModel::setCurrentIndex, this, [&](b8 canBeSet, const QModelIndex& index)
			{
				if (canBeSet)
				{
					m_listView->setRootIndex(index);
					m_breadcrumbs->rebuildBreadcrumbs(index);
				}
			});

		m_breadcrumbs->rebuildBreadcrumbs(m_listView->currentIndex());
	}

	ProjectBrowserView::~ProjectBrowserView()
	{
	}
}
