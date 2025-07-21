#include "TextureImportView.h"

#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
	TextureImportView::TextureImportView(QWidget* pParent) : QDialog(pParent)
	{
		setWindowTitle("Texture Import Options");
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
		setModal(true);
		setAttribute(Qt::WA_DeleteOnClose);

		updateUI();
	}

	TextureImportView::~TextureImportView()
	{
	}

	void TextureImportView::showImportDialog(const QString& srcPath, const QString& dstPath)
	{
		show();
		m_srcPath = srcPath;
		m_dstPath = dstPath;

		QPixmap originalPixmap(m_srcPath);
		if (!originalPixmap.isNull())
		{
			QPixmap scaledPixmap = originalPixmap.scaled(
				m_imagePreview->size(),
				Qt::KeepAspectRatio,
				Qt::SmoothTransformation
			);

			m_imagePreview->setPixmap(scaledPixmap);
			m_imagePreview->setAlignment(Qt::AlignCenter);
		}

		Path path = m_srcPath.toStdString();
		m_nameEdit->setText(QString::fromStdString(path.stem().string()));
		m_imageSize->setText(QString("Image Size: %1x%2")
			.arg(m_imagePreview->pixmap().width())
			.arg(m_imagePreview->pixmap().height()));
		m_formatCombo->setCurrentIndex(0);
	}

	void TextureImportView::resizeEvent(QResizeEvent* event)
	{
		QPixmap originalPixmap(m_srcPath);
		if (!originalPixmap.isNull())
		{
			QPixmap scaledPixmap = originalPixmap.scaled(
				m_imagePreview->size(),
				Qt::KeepAspectRatio,
				Qt::SmoothTransformation
			);

			m_imagePreview->setPixmap(scaledPixmap);
			m_imagePreview->setAlignment(Qt::AlignCenter);
		}
	}

	void TextureImportView::onImportClicked()
	{
		clearFields();
		close();
	}

	void TextureImportView::onCancelClicked()
	{
		clearFields();
		close();
	}

	void TextureImportView::createPreviewSection()
	{
		QHBoxLayout* previewLayout = new QHBoxLayout();
		m_imagePreview = new QLabel(this);
		m_imagePreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_imagePreview->setObjectName("ImagePreview");
		m_imagePreview->setAlignment(Qt::AlignCenter);
		m_imagePreview->setMinimumSize(256, 256);
		m_imagePreview->setStyleSheet(
			"#ImagePreview {"
			"    border: 1px solid #666666;"
			"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
			"        stop:0 #3a3a3a, stop:1 #2d2d2d);"
			"}"
		);

		previewLayout->addWidget(m_imagePreview);
		m_mainLayout->addLayout(previewLayout);
	}

	void TextureImportView::createPropertiesSection()
	{
		m_nameEdit = new QLineEdit(this);
		m_imageSize = new QLabel(this);

		m_formatCombo = new QComboBox(this);
		for(usize i = 0; i < magic_enum::enum_count<ImageFormat>(); i++)
		{
			ImageFormat format = magic_enum::enum_value<ImageFormat>(i);
			if (format != ImageFormat::Undefined)
			{
				QString formatName = QString::fromStdString(String(magic_enum::enum_name(format)));
				m_formatCombo->addItem(formatName, i32(format));
			}
		}

		QHBoxLayout* nameLayout = new QHBoxLayout();
		nameLayout->addWidget(new QLabel("Texture Name:", this));
		nameLayout->addWidget(m_nameEdit);

		QHBoxLayout* formatLayout = new QHBoxLayout();
		formatLayout->addWidget(new QLabel("Texture Format:", this));
		formatLayout->addWidget(m_formatCombo);

		m_mainLayout->addLayout(nameLayout);
		m_mainLayout->addWidget(m_imageSize);
		m_mainLayout->addLayout(formatLayout);
	}

	void TextureImportView::clearFields()
	{
		m_nameEdit->clear();
		m_imageSize->clear();
		m_formatCombo->clear();

		m_imagePreview->clear();
		m_srcPath.clear();
		m_dstPath.clear();
	}

	void TextureImportView::updateUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setContentsMargins(10, 10, 10, 10);
		m_mainLayout->setSpacing(5);

		createPreviewSection();
		createPropertiesSection();

		QHBoxLayout* buttonLayout = new QHBoxLayout();

		m_importButton = new QPushButton("Import", this);
		m_importButton->setAutoDefault(true);
		m_cancelButton = new QPushButton("Cancel", this);
		m_cancelButton->setAutoDefault(false);

		buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
		buttonLayout->addWidget(m_importButton);
		buttonLayout->addWidget(m_cancelButton);

		m_mainLayout->addLayout(buttonLayout);

		connect(m_importButton, &QPushButton::clicked, this, &TextureImportView::onImportClicked);
		connect(m_cancelButton, &QPushButton::clicked, this, &TextureImportView::onCancelClicked);
	}
}
