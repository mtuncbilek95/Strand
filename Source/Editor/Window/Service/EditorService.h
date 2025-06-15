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
	class EditorService : public UIServiceBase
	{
		Q_OBJECT
	public:
		EditorService(QObject* pParent = nullptr) {}
		~EditorService() {}

		void ResetServiceField() override final {}

		template<typename T>
		void RegisterPanel(const QString& name, QWidget* toTarget = nullptr)
		{

		}

		template<typename T>
		T* Get()
		{
			return nullptr;
		}

	public slots:


	private:
		QHash<QString, UIServiceBase*> m_panels;
	};
}