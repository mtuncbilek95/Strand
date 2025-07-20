#include "CreateFolderAction.h"

namespace Flax
{
	CreateFolderAction::CreateFolderAction(const QString& text, QObject* pParent) : QAction(text, pParent)
	{
		connect(this, &QAction::triggered, this, &CreateFolderAction::onTriggered);
	}

	CreateFolderAction::~CreateFolderAction()
	{
	}

	void CreateFolderAction::onCreateFolder(const QModelIndex& index)
	{

	}
}
