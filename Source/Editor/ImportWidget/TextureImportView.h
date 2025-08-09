/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Strand
{
	class TextureImportView : public QDialog
	{
		Q_OBJECT
	public:
		TextureImportView(QWidget* pParent = nullptr);
		~TextureImportView();

		void showImportDialog(const QString& srcPath, const QString& dstPath);

	signals:
		void onImportAccepted(const QString& srcPath, const QString& dstPath);
		void onImportCanceled();

	protected:
		void resizeEvent(QResizeEvent* event) override;

	private slots:
		void onCancelClicked();
		void onImportClicked();

	private:
		void createPreviewSection();
		void createPropertiesSection();
		void clearFields();
		void updateUI();

	private:
		QVBoxLayout* m_mainLayout;
		QLabel* m_imagePreview;
		QLineEdit* m_nameEdit;
		QLabel* m_imageSize;
		QComboBox* m_formatCombo;

		QPushButton* m_importButton;
		QPushButton* m_cancelButton;

		QString m_srcPath;
		QString m_dstPath;
	};
}