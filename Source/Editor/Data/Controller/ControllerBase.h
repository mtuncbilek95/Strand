/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

namespace Flax
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

