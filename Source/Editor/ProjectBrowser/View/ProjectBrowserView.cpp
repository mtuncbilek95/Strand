#include "ProjectBrowserView.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>


#include <Editor/ProjectBrowser/View/ProjectListView.h>
#include <Editor/ProjectBrowser/View/ProjectWatcherView.h>
#include <Editor/ProjectBrowser/Model/ProjectBrowserFilterProxy.h>
#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserViewModel.h>
#include <Editor/ProjectBrowser/ViewModel/ProjectBrowserIconProvider.h>

namespace Flax
{
	ProjectBrowserView::ProjectBrowserView(QWidget* pParent) : QWidget(pParent)
	{
		m_viewModel = ViewModelRegistry::Get().ViewModel<ProjectBrowserViewModel>().get();
		m_listView = new ProjectListView(this);

		auto* fsModel = m_viewModel->Model();
		QString mountPoint = QString::fromStdString(RuntimeService::Get<VirtualFileService>()->AbsolutePath("Assets").string());
		m_viewModel->IconProvider()->setIcons();

		m_listView->setModel(m_viewModel->Proxy());
		fsModel->setRootPath(mountPoint);
		QModelIndex rootIndex = m_viewModel->Proxy()->mapFromSource(fsModel->index(mountPoint));
		m_listView->setRootIndex(rootIndex);

		m_breadcrumbs = new ProjectWatcherView(this);
		m_breadcrumbs->rebuildWatcher(m_listView->rootIndex());

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addWidget(m_breadcrumbs);
		layout->addWidget(m_listView);
		layout->setStretch(0, 1);
		layout->setStretch(1, 8);

		connect(m_listView, &ProjectListView::activated, this, &ProjectBrowserView::onDoubleClicked);
		connect(m_breadcrumbs, &ProjectWatcherView::onWatcherClicked, this, &ProjectBrowserView::onDoubleClicked);
	}

	ProjectBrowserView::~ProjectBrowserView()
	{
	}

	void ProjectBrowserView::onDoubleClicked(const QModelIndex& index)
	{
		if (!index.isValid())
			return;

		QModelIndex modelIndex = m_viewModel->Proxy()->mapToSource(index);
		if (!m_viewModel->Model()->isDir(modelIndex))
			return;

		m_listView->setRootIndex(index);
		m_breadcrumbs->rebuildWatcher(index);
	}
}
