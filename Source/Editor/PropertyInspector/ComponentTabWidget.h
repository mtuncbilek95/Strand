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
	class ComponentTabWidget : public QWidget
	{
		Q_OBJECT
	public:
		ComponentTabWidget(const QString& name, QWidget* pParent = nullptr);
		~ComponentTabWidget() override = default;

	signals:
		void onComponentChecked(b8 state);

	private slots:
		void onComponentStateChanged(i32 state);

	private:
		QLabel* m_nameLabel;
		QCheckBox* m_enableCheckbox;
	};
}