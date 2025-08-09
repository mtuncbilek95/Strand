/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

namespace Strand
{
	class ControllerBase : public QObject
	{
		Q_OBJECT
	public:
		virtual ~ControllerBase() = default;

		virtual void InitializeController() = 0;
		virtual void ShutdownController() = 0;
	};
}

