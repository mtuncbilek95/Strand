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
	class Scene;
	class MeshManagement;

	/*
	 * The idea is to have a single point of entry for all renderComponents
	 * in the scene. Those render components will know where to go with the
	 * help of their material objects. Resolve will read the material and
	 * decide where to go in renderGraph. RenderResolver will probably wait 
	 * physics resolvement and animation resolvement to finish before it 
	 * starts its work (Most probably). But with multi-thread, everything can
	 * be done in parallel which makes it a lot more complicated and we may
	 * need a cpu semaphore. Idk... 
	 * 
	 * RenderResolver reads renderComponent, gets the proper material and mesh
	 * from MeshManagement and then sends it to the correct renderGraph.
	 */

	/**
	 * @class RenderResolver
	 * @brief Handles the use cases of every renderable objects in the 
	 * scene via MeshManagement and RenderGraph.
	 */
	class RenderResolver
	{
	public:
		RenderResolver(MeshManagement* manager);
		~RenderResolver() = default;

		void Resolve(Scene* scene);

	private:
		MeshManagement* m_meshManager;
		RenderGraphManagement* m_dagManager;
	};
}