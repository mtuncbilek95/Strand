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
	class NoExtensionDelegate : public QStyledItemDelegate
	{
		Q_OBJECT
	public:
		NoExtensionDelegate(QObject* pParent = nullptr);
		~NoExtensionDelegate() override = default;

		QString displayText(const QVariant& value, const QLocale& locale) const override;
	};
}
