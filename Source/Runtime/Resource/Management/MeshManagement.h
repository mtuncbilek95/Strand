/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Flax
{
	class MeshResource;
	class MaterialResource;

	class MeshManagement
	{
	public:
		MeshManagement();
		~MeshManagement();

		void RegisterMesh();
		void UnregisterMesh();

		void RegisterMaterial();
		void UnregisterMaterial();

		u32 GetMeshResource();
		u32 GetMaterialResource();

	private:
		HashMap<u32, Ref<MeshResource>> m_meshes;
		HashMap<u32, Ref<MaterialResource>> m_materials;
	};
}