/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/VirtualFile/VirtualFileSystem.h>

namespace Flax
{
	class VFSService final : public ServiceBase
	{
	public:
		void InitVFS(VFSType type, const String& rootPath);
		void ResetServiceField() override final;

		VirtualFileSystem* VFS() const { return m_service.get(); }

	private:
		Ref<VirtualFileSystem> m_service;
	};
}
