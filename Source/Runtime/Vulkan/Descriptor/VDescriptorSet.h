/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
	class VDescLayout;
	class VDescPool;
	class VImageView;
	class VSampler;
	class VBuffer;

	struct DescSetProps final
	{
		VDescLayout* layout;
		VDescPool* pool;
	};

	struct ImageResource final
	{
		VImageView* image;
		VSampler* sampler;
	};

	union ResourceEntry final
	{
		VBuffer* uniform;
		ImageResource image;
	};

	struct UpdateEntry final
	{
		ResourceEntry entry;
		VkDescriptorType type;
		u32 count;
		u32 arrayElement;
		u64 bufferOffset;
		u32 binding;
	};

	struct SetUpdateProps final
	{
		Vector<UpdateEntry> entries;
	};

	class VDescSet final : public VObject
	{
	public:
		VDescSet(const DescSetProps& desc, VDevice* pDevice);
		~VDescSet() override final;

		inline VkDescriptorSet GetVkSet() const { return m_set; }

		void UpdateData(const SetUpdateProps& desc);

	private:
		DescSetProps m_props;

		VkDescriptorSet m_set;
	};
}