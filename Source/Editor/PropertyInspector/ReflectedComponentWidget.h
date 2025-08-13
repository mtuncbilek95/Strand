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
	class IComponent;
	class ComponentTabWidget;

	class ReflectedComponentWidget : public QWidget
	{
		Q_OBJECT
	public:
		ReflectedComponentWidget(IComponent* pComponent, QWidget* pParent = nullptr);
		~ReflectedComponentWidget() override;

	private slots:
		void onComponentChecked(b8 state);

	private:
		IComponent* m_component;
		ComponentTabWidget* m_titleWidget;

		QVector<QMetaObject::Connection> m_connections;
	};
}