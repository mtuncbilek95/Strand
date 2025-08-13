#include "DomainViewWidget.h"

#include <Editor/DomainView/IconProvider/DomainIconProvider.h>
#include <Editor/DomainView/Proxy/DomainFilterProxy.h>
#include <Editor/DomainView/DomainMiscView.h>
#include <Editor/DomainView/DomainListView.h>

#include <Editor/SceneGraph/SceneGraphController.h>

namespace Strand
{
	DomainViewWidget::DomainViewWidget(QWidget* pParent) : QWidget(pParent)
	{
		m_provider = new DomainIconProvider();
		m_provider->setIcons();
		m_proxy = new DomainFilterProxy(this);
		m_miscView = new DomainMiscView(this);
		m_listView = new DomainListView(this);

		auto vfm = ServiceLocator::Get<VirtualFileService>();
		QString rootPath = QString::fromStdString(vfm->AbsolutePath("Assets").string());
		m_fsModel.setRootPath(rootPath);
		m_fsModel.setReadOnly(false);
		m_fsModel.setIconProvider(m_provider);
		m_proxy->setSourceModel(&m_fsModel);
		
		m_listView->setModel(m_proxy);
		m_listView->setRootIndex(m_proxy->mapFromSource(m_fsModel.index(rootPath)));
		emit m_miscView->onRefreshPathView(rootPath);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addWidget(m_miscView);
		layout->addWidget(m_listView);

		setupSignals();
	}

	void DomainViewWidget::onAddDomainClicked()
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void DomainViewWidget::onImportDomainClicked()
	{
		EDITOR_NOT_IMPLEMENTED_YET(void());
	}

	void DomainViewWidget::onBackDomainClicked()
	{
		QModelIndex proxyIndex = m_listView->rootIndex();
		QModelIndex sourceIndex = m_proxy->mapToSource(proxyIndex);
		proxyIndex = m_proxy->mapFromSource(sourceIndex.parent());

		if (proxyIndex.isValid() && sourceIndex != m_fsModel.index(m_fsModel.rootPath()))
		{
			m_listView->setRootIndex(proxyIndex);
			emit onRefreshPathView(m_fsModel.fileInfo(sourceIndex.parent()).absoluteFilePath());
		}
	}

	void DomainViewWidget::onDomainActivated(const QModelIndex& proxyIndex)
	{
		if (!proxyIndex.isValid())
			return;

		QModelIndex sourceIndex = m_proxy->mapToSource(proxyIndex);
		if (!m_fsModel.isDir(sourceIndex))
		{
			QFileInfo fileInfo(m_fsModel.filePath(sourceIndex));
			qDebug() << fileInfo.baseName();
			emit onFileActivated(m_fsModel.filePath(sourceIndex));
			return;
		}

		m_listView->setRootIndex(proxyIndex);
		emit onRefreshPathView(m_fsModel.fileInfo(sourceIndex).absoluteFilePath());
	}

	void DomainViewWidget::onPathViewClicked(const QString& path)
	{
		auto vfm = ServiceLocator::Get<VirtualFileService>();
		Path virtualPath = vfm->VirtualPath(path.toStdString());
		if (virtualPath.empty())
			return;
		QModelIndex sourceIndex = m_fsModel.index(QString::fromStdString(vfm->AbsolutePath(virtualPath).string()));
		QModelIndex proxyIndex = m_proxy->mapFromSource(sourceIndex);
		if (proxyIndex.isValid())
		{
			m_listView->setRootIndex(proxyIndex);
			emit onRefreshPathView(m_fsModel.fileInfo(sourceIndex).absoluteFilePath());
		}
	}

	void DomainViewWidget::setupSignals()
	{
		connect(m_listView, &DomainListView::activated, this, &DomainViewWidget::onDomainActivated);
		connect(m_miscView, &DomainMiscView::onAddClicked, this, &DomainViewWidget::onAddDomainClicked);
		connect(m_miscView, &DomainMiscView::onImportClicked, this, &DomainViewWidget::onImportDomainClicked);
		connect(m_miscView, &DomainMiscView::onBackClicked, this, &DomainViewWidget::onBackDomainClicked);
		connect(this, &DomainViewWidget::onRefreshPathView, m_miscView, &DomainMiscView::onRefreshPathView); // Reset breadcrumbs
		connect(m_miscView, &DomainMiscView::onPathViewClicked, this, &DomainViewWidget::onPathViewClicked); // Breadcrumbs clicked

		connect(this, &DomainViewWidget::onFileActivated, ControllerManager::Get<SceneGraphController>(), &SceneGraphController::onSceneLoadRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &TextureViewController::Get(), &TextureViewController::onTextureViewRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &MaterialViewController::Get(), &MaterialViewController::onMaterialGraphRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &MeshViewController::Get(), &MeshViewController::onMeshViewRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &AudioViewController::Get(), &AudioViewController::onAudioGraphRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &AnimationViewController::Get(), &AnimationViewController::onAnimationSequenceRequested);
		// connect(this, &DomainViewWidget::onFileActivated, &RenderGraphController::Get(), &RenderGraphController::onRenderGraphRequested);
	}
}
