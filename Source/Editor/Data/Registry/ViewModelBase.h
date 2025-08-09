/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
	class ViewModelBase : public QObject
	{
		Q_OBJECT
	public:
		ViewModelBase(QObject* pParent = nullptr) : QObject(pParent) {}
		virtual ~ViewModelBase() = default;
	};
}
