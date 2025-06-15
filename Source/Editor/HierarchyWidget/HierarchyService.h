/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Editor/Core/CoreMinimal.h>

namespace Flax
{
	class HierarchyItemModel;
	class InspectorListModel;
	class HierarchyWidget;
	class InspectorWidget;

	class HierarchyService final : public UIServiceBase
	{
		Q_OBJECT
	public:
		HierarchyService(QObject* parent = nullptr);
		~HierarchyService() = default;

		void setHierarchy(HierarchyWidget* widget) { m_hWidget = widget; }
		HierarchyItemModel* HierarchyModel() const { return m_hModel.get(); }

		void setInspector(InspectorWidget* widget) { m_iWidget = widget; }
		InspectorListModel* InspectorModel() const { return m_iModel.get(); }

		void ResetServiceField() override final {}

	public slots:
		void onItemSelected(const QModelIndex& index);
		void onContextMenuRequested(const QPoint& pos);
		void onItemDoubleClicked(const QModelIndex& index);

	protected:
		bool eventFilter(QObject* pWatched, QEvent* pEvent) override;

	private:
		Ref<HierarchyItemModel> m_hModel;
		HierarchyWidget* m_hWidget = nullptr;

		Ref<InspectorListModel> m_iModel;
		InspectorWidget* m_iWidget = nullptr;
	};
}
