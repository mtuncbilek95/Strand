#include "FileMenu.h"

namespace Flax
{
	FileMenu::FileMenu(QWidget* pParent) : QMenu(pParent)
	{
		setTitle("File");
		setObjectName("FileMenu");

		// Add default actions
		m_actions["New"] = addAction("New");
		m_actions["Open"] = addAction("Open");
		m_actions["Save"] = addAction("Save");
		m_actions["SaveAs"] = addAction("Save As");
		m_actions["Exit"] = addAction("Exit");

		connect(this, &QMenu::triggered, this, &FileMenu::onActionTriggered);
	}
	
	FileMenu::~FileMenu()
	{
	}
	
	void FileMenu::registerAction(const QString& actionName)
	{
	}

	void FileMenu::unregisterAction(const QString& actionName)
	{
	}

	void FileMenu::onActionTriggered(QAction* pAction)
	{
		emit onActionSignalled(pAction->text(), pAction);
	}
}
