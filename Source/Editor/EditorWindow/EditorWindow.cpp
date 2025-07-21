#include "EditorWindow.h"

#include <Editor/SceneRenderer/SceneRendererWidget.h>

namespace Flax
{
	EditorWindow::EditorWindow(QWidget* pParent)
	{
		setObjectName("EditorWindow");
		setWindowTitle("Flax Editor");
		setMinimumSize(1920, 1080);
		setAttribute(Qt::WA_DeleteOnClose, true);
		setContentsMargins(4, 4, 4, 4);

		m_topMenuBar = new QMenuBar(this);
		m_topMenuBar->addMenu(new QMenu("File"));
		m_topMenuBar->addMenu(new QMenu("View"));
		m_topMenuBar->addMenu(new QMenu("Window"));
		m_topMenuBar->addMenu(new QMenu("Tools"));
		m_topMenuBar->addMenu(new QMenu("Build"));
		m_topMenuBar->addMenu(new QMenu("Help"));
		setMenuBar(m_topMenuBar);

		QDockWidget* leftDock = new QDockWidget(this);
		m_tabWidgets[TabDirection::Left] = new QTabWidget(leftDock);
		leftDock->setTitleBarWidget(new QWidget());
		leftDock->setMinimumWidth(256);
		leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		leftDock->setWidget(m_tabWidgets[TabDirection::Left]);

		QDockWidget* rightDock = new QDockWidget(this);
		m_tabWidgets[TabDirection::Right] = new QTabWidget(rightDock);
		rightDock->setTitleBarWidget(new QWidget());
		rightDock->setMinimumWidth(256);
		rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		rightDock->setWidget(m_tabWidgets[TabDirection::Right]);

		QDockWidget* bottomDock = new QDockWidget(this);
		m_tabWidgets[TabDirection::Bottom] = new QTabWidget(bottomDock);
		bottomDock->setTitleBarWidget(new QWidget());
		bottomDock->setMinimumHeight(256);
		bottomDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		bottomDock->setWidget(m_tabWidgets[TabDirection::Bottom]);

		addDockWidget(Qt::LeftDockWidgetArea, leftDock);
		addDockWidget(Qt::RightDockWidgetArea, rightDock);
		addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

		auto* ctrW = new SceneRendererWidget(this);
		setCentralWidget(ctrW);
	}

	EditorWindow::~EditorWindow()
	{
	}

	void EditorWindow::addTabTo(TabDirection dir, QWidget* widget, const QString& titleName)
	{
		if (m_tabWidgets.contains(dir))
		{
			QTabWidget* tabWidget = m_tabWidgets[dir];
			if (tabWidget)
			{
				tabWidget->addTab(widget, titleName);
				tabWidget->setCurrentWidget(widget);
			}
		}
		else
			Log::Error(LogType::Editor, "Invalid tab direction specified for adding widget.");
	}
}
