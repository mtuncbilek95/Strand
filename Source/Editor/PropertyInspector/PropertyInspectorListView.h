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
	class Entity;
	class IComponent;
	class ReflectedComponentWidget;
	class ComponentTabWidget;

	class PropertyInspectorListView : public QListWidget
	{
		Q_OBJECT
	public:
		PropertyInspectorListView(QWidget* pParent = nullptr);
		~PropertyInspectorListView() override = default;

	public slots:
		void onEntitySelected(Entity* pEntity);
		void onEntityDeselected(Entity* pEntity);

	protected:
		void resizeEvent(QResizeEvent* pEvent) override;
		void mousePressEvent(QMouseEvent* pEvent) override;
		void mouseReleaseEvent(QMouseEvent* pEvent) override;
		void mouseMoveEvent(QMouseEvent* pEvent) override;
		void keyPressEvent(QKeyEvent* pEvent) override;
		void keyReleaseEvent(QKeyEvent* pEvent) override;
		void wheelEvent(QWheelEvent* pEvent) override;
		void contextMenuEvent(QContextMenuEvent* pEvent) override;

	private:
		void createComponentWidgets();
		void clearComponentWidgets();
		
		i32 calculateMinimumWidth() const;
	private:
		Entity* m_selectedEntity = nullptr;
	};
}