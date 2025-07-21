/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>

namespace Flax
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