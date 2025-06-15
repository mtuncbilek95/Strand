#include "EditorWindow.h"

#include <Editor/SceneWidget/SceneWidget.h>
#include <Editor/SceneWidget/SceneControlWidget.h>
#include <Editor/TerminalWidget/TerminalWidget.h>
#include <Editor/HierarchyWidget/HierarchyWidget.h>
#include <Editor/InspectorWidget/InspectorWidget.h>

namespace Flax
{
	EditorWindow::EditorWindow(QWidget* pParent) : QMainWindow(pParent)
	{
		setObjectName("EditorWindow");
		setWindowTitle("Flax Editor");
		setMinimumSize(800, 600);
		setAttribute(Qt::WA_DeleteOnClose, true);

		m_scene = new SceneWidget();
		m_sceneControl = new SceneControlWidget();

		QDockWidget* outliner = new QDockWidget("Hierarchy", this);
		outliner->setWidget(new HierarchyWidget());
		addDockWidget(Qt::LeftDockWidgetArea, outliner);

		auto console = new QDockWidget("Console", this);
		console->setWidget(new TerminalWidget(this));
		addDockWidget(Qt::BottomDockWidgetArea, console);

		auto inspect = new QDockWidget("Inspector", this);
		inspect->setWidget(new InspectorWidget(this));
		addDockWidget(Qt::RightDockWidgetArea, inspect);

		QWidget* centerContainer = new QWidget();
		QVBoxLayout* middleLayout = new QVBoxLayout(centerContainer);
		middleLayout->addWidget(m_sceneControl);
		middleLayout->addWidget(m_scene);

		setCentralWidget(centerContainer);
	}

	EditorWindow::~EditorWindow()
	{
	}

	void EditorWindow::RunEditor()
	{
		resize(1920, 1080);
		m_scene->RunScene();
	}
}
