#include "EditorWindow.h"

#include <Editor/EditorWindow/ViewModel/EditorWindowViewModel.h>
#include <Editor/SceneRenderer/View/SceneRendererView.h>

namespace Flax
{
	EditorWindow::EditorWindow(QWidget* pParent) : QMainWindow(pParent)
	{
		m_viewModel = ViewModelRegistry::Get().ViewModel<EditorWindowViewModel>().get();
		m_viewModel->Construct();

		setObjectName("EditorWindow");
		setWindowTitle("Flax Editor");
		setMinimumSize(1280, 720);
		setAttribute(Qt::WA_DeleteOnClose, true);

		QDockWidget* leftDock = new QDockWidget("", this);
		leftDock->setTitleBarWidget(new QWidget());
		leftDock->setMinimumWidth(256);
		leftDock->setObjectName("EditorWindow_RightDock");
		leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		leftDock->setWidget(m_viewModel->Deck(EditorDirection::DirectionLeft));
		addDockWidget(Qt::LeftDockWidgetArea, leftDock);

		QDockWidget* bottomDock = new QDockWidget("", this);
		bottomDock->setTitleBarWidget(new QWidget());
		bottomDock->setMinimumHeight(256);
		bottomDock->setObjectName("EditorWindow_BottomDock");
		bottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
		bottomDock->setWidget(m_viewModel->Deck(EditorDirection::DirectionBottom));
		addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

		QDockWidget* rightDock = new QDockWidget("", this);
		rightDock->setTitleBarWidget(new QWidget());
		rightDock->setObjectName("EditorWindow_RightDock");
		rightDock->setMinimumWidth(256);
		rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
		rightDock->setWidget(m_viewModel->Deck(EditorDirection::DirectionRight));
		addDockWidget(Qt::RightDockWidgetArea, rightDock);

		setCentralWidget(new SceneRendererView(this));
	}

	EditorWindow::~EditorWindow()
	{
	}
}
