#include "DomainMiscView.h"

#include <Editor/DomainView/DomainPathView.h>

namespace Flax
{
	DomainMiscView::DomainMiscView(QWidget* pParent) : QWidget(pParent)
	{
		setObjectName("DomainMiscView_Widget");
		setFixedHeight(32);

		QHBoxLayout* mainLayout = new QHBoxLayout(this);

		m_addButton = new QPushButton(this);
		m_addButton->setText("Add");
		m_addButton->setIcon(QIcon(":/Icons/ContentBrowser/PB_Add.svg"));
		m_addButton->setLayoutDirection(Qt::LeftToRight);

		QFontMetrics fm(m_addButton->font());
		i32 btnWidth = fm.horizontalAdvance(m_addButton->text()) + 32;
		m_addButton->setFixedWidth(btnWidth);
		
		m_importButton = new QPushButton(this);
		m_importButton->setText("Import");
		m_importButton->setIcon(QIcon(":/Icons/ContentBrowser/PB_Import.svg"));
		m_importButton->setLayoutDirection(Qt::LeftToRight);

		m_backButton = new QPushButton(this);
		m_backButton->setIcon(QIcon(":/Icons/ContentBrowser/PB_MoveBack.svg"));
		m_backButton->setLayoutDirection(Qt::LeftToRight);

		m_pathView = new DomainPathView(this);

		mainLayout->setContentsMargins(0, 2, 0, 2);
		mainLayout->setSpacing(2);
		mainLayout->setAlignment(Qt::AlignLeft);

		mainLayout->addWidget(m_addButton);
		mainLayout->addWidget(m_importButton);
		mainLayout->addWidget(m_backButton);
		mainLayout->addWidget(m_pathView);

		setupSignals();
	}

	void DomainMiscView::setupSignals()
	{
		connect(m_addButton, &QPushButton::clicked, this, &DomainMiscView::onAddClicked);
		connect(m_importButton, &QPushButton::clicked, this, &DomainMiscView::onImportClicked);
		connect(m_backButton, &QPushButton::clicked, this, &DomainMiscView::onBackClicked);
		connect(this, &DomainMiscView::onRefreshPathView, m_pathView, &DomainPathView::refreshPathView);
		connect(m_pathView, &DomainPathView::onPathViewClicked, this, &DomainMiscView::onPathViewClicked); 
	}
}
