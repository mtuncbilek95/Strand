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
	class HierarchyWidget;

	class HierarchyService final : public UIServiceBase
	{
		Q_OBJECT
	public:
		HierarchyService(QObject* parent = nullptr);
		~HierarchyService() = default;

		void setWidget(HierarchyWidget* widget) { m_hWidget = widget; }
		HierarchyItemModel* Model() const { return m_model.get(); }

		void ResetServiceField() override final {}

	public slots:
		void onItemSelected(const QModelIndex& index);
		void onContextMenuRequested(const QPoint& pos);
		void onItemDoubleClicked(const QModelIndex& index);

	protected:
		bool eventFilter(QObject* pWatched, QEvent* pEvent) override;

	private:
		Ref<HierarchyItemModel> m_model;
		HierarchyWidget* m_hWidget = nullptr;
	};
}
