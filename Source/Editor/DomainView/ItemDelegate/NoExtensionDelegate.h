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
	class NoExtensionDelegate : public QStyledItemDelegate
	{
		Q_OBJECT
	public:
		NoExtensionDelegate(QObject* pParent = nullptr);
		~NoExtensionDelegate() = default;

		QString displayText(const QVariant& value, const QLocale& locale) const override;
	};
}
