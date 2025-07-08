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
#include <Editor/EditorWindow/ViewModel/EditorDirection.h>

namespace Flax
{
	class EditorWindowViewModel : public ViewModelBase
	{
		Q_OBJECT
	public:
		EditorWindowViewModel(QObject* pParent = nullptr);
		~EditorWindowViewModel();

		void Construct();
		void AddTab(EditorDirection dir, QWidget* pWidget, const QString& printedName);

		QTabWidget* Deck(EditorDirection dir) { return m_deck.at(dir); }

	private:
		HashMap<EditorDirection, QTabWidget*> m_deck;
	};
}