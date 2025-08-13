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
	class PropertyInspectorListView;

	class PropertyInspectorWidget : public QWidget
	{
		Q_OBJECT
	public:
		PropertyInspectorWidget(QWidget* pParent = nullptr);
		~PropertyInspectorWidget() override = default;

	private slots:
		void onAddComponentClicked();

	private:
		PropertyInspectorListView* m_propertyView;
		QPushButton* m_addComponentButton;
	};
}