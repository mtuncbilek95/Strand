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
	class ContentItemModel;
	class ProjectContentWidget;

	class ProjectContentService : public UIServiceBase
	{
		Q_OBJECT
	public:
		ProjectContentService(QObject* parent = nullptr);
		virtual ~ProjectContentService() = default;

		void setContentBrowser(ProjectContentWidget* widget) { m_cWidget = widget; }
		ContentItemModel* ContentModel() const { return m_cModel.get(); }

		void ResetServiceField() override final {}

	private:
		Ref<ContentItemModel> m_cModel;
		ProjectContentWidget* m_cWidget;
	};
}
