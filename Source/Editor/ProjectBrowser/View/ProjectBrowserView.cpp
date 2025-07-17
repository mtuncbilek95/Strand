#include "ProjectBrowserView.h"

#include <Editor/Data/CustomPBV/CustomPBV.h>
#include <Editor/ProjectBrowser/View/ProjectWatcherView.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserModel.h>
#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserViewModel.h>

namespace Flax
{
	ProjectBrowserView::ProjectBrowserView(QWidget* pParent) : QWidget(pParent)
	{
		m_viewModel = ViewModelRegistry::Get().ViewModel<ProjectBrowserViewModel>().get();
		m_viewModel->SetModel(new ProjectBrowserModel(m_viewModel));

		m_listView = new CustomPBV(this);
		m_listView->setModel(m_viewModel->Model());

		m_breadcrumbs = new ProjectWatcherView(this);
		m_breadcrumbs->rebuildWatcher(m_listView->rootIndex());

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addWidget(m_breadcrumbs);
		layout->addWidget(m_listView);
		layout->setStretch(0, 1);
		layout->setStretch(1, 8);

		connect(m_listView, &QListView::activated, m_viewModel, &ProjectBrowserViewModel::onItemDoubleClicked);
		connect(m_viewModel, &ProjectBrowserViewModel::setCurrentIndex, this, &ProjectBrowserView::onDoubleClicked);
		connect(m_breadcrumbs, &ProjectWatcherView::onWatcherClicked, this, &ProjectBrowserView::onDoubleClicked);
	}

	ProjectBrowserView::~ProjectBrowserView()
	{
	}

	void ProjectBrowserView::onDoubleClicked(const QModelIndex& index)
	{
		m_listView->setRootIndex(index);
		m_breadcrumbs->rebuildWatcher(index);
	}
}
