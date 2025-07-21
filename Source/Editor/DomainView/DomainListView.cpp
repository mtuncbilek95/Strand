#include "DomainListView.h"

#include <Runtime/FileSystem/IVirtualFileNode.h>
#include <Runtime/FileSystem/IVirtualFileSystem.h>
#include <Runtime/FileSystem/Service/VirtualFileService.h>

#include <Editor/ImportWidget/TextureImportView.h>

namespace Flax
{
	DomainListView::DomainListView(QWidget* pParent) : QListView(pParent)
	{
		setViewMode(QListView::IconMode);
		setDragDropMode(QAbstractItemView::DragDrop);
		setDragEnabled(true);
		setAcceptDrops(true);
		setDropIndicatorShown(true);
		setDefaultDropAction(Qt::MoveAction);
		setUniformItemSizes(true);
		setIconSize(QSize(96, 96));
		setGridSize(QSize(128, 128));
		setSpacing(12);
		setResizeMode(QListView::Adjust);
		setSelectionMode(QAbstractItemView::ExtendedSelection);
		setEditTriggers(QAbstractItemView::EditKeyPressed |
			QAbstractItemView::SelectedClicked);
	}

	DomainListView::~DomainListView()
	{
	}

	void DomainListView::onCreateFolder(const QModelIndex& sourceIndex)
	{
		QFileSystemModel* sourceModel = qobject_cast<QFileSystemModel*>(qobject_cast<QSortFilterProxyModel*>(model())->sourceModel());
		auto vfm = RuntimeService::Get<VirtualFileService>();
		Path virtualPath = vfm->VirtualPath(sourceModel->filePath(sourceIndex).toStdString());

		String folderName = "New_Folder";
		Path folderPath = virtualPath / (folderName + "/");
		i32 counter = 1;
		while (vfm->Exists(folderPath))
		{
			folderName = "New_Folder_" + std::to_string(counter++);
			folderPath = virtualPath / (folderName + "/");
		}

		vfm->Create(folderPath);
		QTimer::singleShot(100, [this, folderPath]()
			{
				startRenameForNewFolder(folderPath);
			});
	}

	void DomainListView::dragEnterEvent(QDragEnterEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void DomainListView::dragMoveEvent(QDragMoveEvent* pEvent)
	{
		if (pEvent->mimeData()->hasUrls())
			pEvent->acceptProposedAction();
		else
			pEvent->ignore();
	}

	void DomainListView::dragLeaveEvent(QDragLeaveEvent* pEvent)
	{
		QListView::dragLeaveEvent(pEvent);
	}

	void DomainListView::dropEvent(QDropEvent* pEvent)
	{
		QString abs = pEvent->mimeData()->urls()[0].toLocalFile();

		Path srcPath = abs.toStdString();
		
		if (srcPath.extension().string() == ".png")
		{
			TextureImportView* importView = new TextureImportView();
			importView->showImportDialog(abs, "");
		}
	}

	void DomainListView::contextMenuEvent(QContextMenuEvent* pEvent)
	{
		QMenu contextMenu = QMenu(this);
		contextMenu.setAttribute(Qt::WA_DeleteOnClose);
		QModelIndex proxyIndex = indexAt(pEvent->pos());

		if (!proxyIndex.isValid())
			proxyIndex = rootIndex();

		QAction* importAsset = contextMenu.addAction("Import Asset");
		contextMenu.addSeparator();

		QAction* createFolder = contextMenu.addAction("Create Folder");
		QAction* createScene = contextMenu.addAction("Create Scene");
		QAction* createRenderGraph = contextMenu.addAction("Create Render Graph");
		contextMenu.addSeparator();

		QAction* selectedAction = contextMenu.exec(pEvent->globalPos());

		if (selectedAction == createFolder)
		{
			QModelIndex sourceIndex = qobject_cast<QSortFilterProxyModel*>(model())->mapToSource(rootIndex());
			emit onCreateFolder(sourceIndex);
		}
	}

	void DomainListView::keyPressEvent(QKeyEvent* pEvent)
	{
		switch(pEvent->key())
		{
			case Qt::Key_F2:
			{
				if (currentIndex().isValid())
					edit(currentIndex());
				break;
			}
			case Qt::Key_Delete:
			{
				QModelIndexList indices = selectedIndexes();
				if (!indices.isEmpty())
				{
					for (const QModelIndex& index : indices)
					{
						QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(model());
						QFileSystemModel* fsModel = qobject_cast<QFileSystemModel*>(proxyModel->sourceModel());

						QModelIndex sourceIndex = proxyModel->mapToSource(index);
						QString absPath = fsModel->filePath(sourceIndex);

						auto vfm = RuntimeService::Get<VirtualFileService>();
						Path virtualPath = vfm->VirtualPath(absPath.toStdString());
						vfm->Delete(virtualPath);
					}
				}
				break;
			}
			default:
				QListView::keyPressEvent(pEvent);
				break;
		}
	}

	void DomainListView::startRenameForNewFolder(const Path& folderPath)
	{
		QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(this->model());
		QFileSystemModel* sourceModel = qobject_cast<QFileSystemModel*>(proxyModel->sourceModel());
		auto vfm = RuntimeService::Get<VirtualFileService>();

		if (!sourceModel || !proxyModel) 
			return;
		m_newItemPath = QString::fromStdString(vfm->AbsolutePath(folderPath).string());

		QModelIndex sourceIndex = sourceModel->index(m_newItemPath);
		if (!sourceIndex.isValid()) 
			return;

		QModelIndex proxyIndex = proxyModel->mapFromSource(sourceIndex);
		if (!proxyIndex.isValid()) 
			return;

		connect(itemDelegate(), &QAbstractItemDelegate::commitData, this, &DomainListView::onEditorCommitted);
		connect(itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &DomainListView::onEditorClosed);

		setCurrentIndex(proxyIndex);
		scrollTo(proxyIndex);
		edit(proxyIndex);
	}

	void DomainListView::onEditorCommitted(QWidget* pEditor)
	{
		QString newName;

		if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(pEditor))
			newName = lineEdit->text();
		else if (QTextEdit* textEdit = qobject_cast<QTextEdit*>(pEditor))
			newName = textEdit->toPlainText();

		QDir oldDir = QDir(m_newItemPath);
		oldDir.cdUp();
		m_newItemPath = oldDir.absolutePath() + "/" + newName + "/";

		auto vfm = RuntimeService::Get<VirtualFileService>();
		Path virtualPath = vfm->VirtualPath(m_newItemPath.toStdString());
		vfm->Refresh(virtualPath.parent_path());

		m_newItemPath.clear();

		disconnect(itemDelegate(), &QAbstractItemDelegate::commitData,
			this, &DomainListView::onEditorCommitted);
		disconnect(itemDelegate(), &QAbstractItemDelegate::closeEditor,
			this, &DomainListView::onEditorClosed);
	}

	void DomainListView::onEditorClosed(QWidget* pEditor, QAbstractItemDelegate::EndEditHint hint)
	{
		Q_UNUSED(pEditor);

		if (!m_newItemPath.isEmpty())
		{
			if(hint == QAbstractItemDelegate::RevertModelCache)
			{
				auto vfm = RuntimeService::Get<VirtualFileService>();
				Path virtualPath = vfm->VirtualPath(m_newItemPath.toStdString());
				vfm->Delete(virtualPath.parent_path());
			}

			disconnect(itemDelegate(), &QAbstractItemDelegate::commitData,
				this, &DomainListView::onEditorCommitted);
			disconnect(itemDelegate(), &QAbstractItemDelegate::closeEditor,
				this, &DomainListView::onEditorClosed);

			m_newItemPath.clear();
		}
	}
}
