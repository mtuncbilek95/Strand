/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/SamplerFormat.h>
#include <Runtime/Graphics/RHI/Util/PipelineFormat.h>

namespace Strand
{
	struct GfxSamplerDesc
	{
		SamplerFilter magFilter = SamplerFilter::Nearest;
		SamplerFilter minFilter = SamplerFilter::Nearest;
		SamplerMipMap mipmapMode = SamplerMipMap::Nearest;
		SamplerAddress addressModeU = SamplerAddress::Repeat;
		SamplerAddress addressModeV = SamplerAddress::Repeat;
		SamplerAddress addressModeW = SamplerAddress::Repeat;
		f32 mipLodBias = 0.f;
		b8 anisotropyEnable = true;
		f32 maxAnisotropy = 16.f;
		b8 compareEnable = true;
		CompareOp compareOp = CompareOp::Always;
		f32 minLod = 0.f;
		f32 maxLod = 1.f;
		BorderColor borderColor = BorderColor::TransparentBlack_Float;

		GfxSamplerDesc& setMagFilter(SamplerFilter filter) { magFilter = filter; return *this; }
		GfxSamplerDesc& setMinFilter(SamplerFilter filter) { minFilter = filter; return *this; }
		GfxSamplerDesc& setMipMapMode(SamplerMipMap mode) { mipmapMode = mode; return *this; }
		GfxSamplerDesc& setAddressModeU(SamplerAddress address) { addressModeU = address; return *this; }
		GfxSamplerDesc& setAddressModeV(SamplerAddress address) { addressModeV = address; return *this; }
		GfxSamplerDesc& setAddressModeW(SamplerAddress address) { addressModeW = address; return *this; }
		GfxSamplerDesc& setMipLodBias(f32 bias) { mipLodBias = bias; return *this; }
		GfxSamplerDesc& setAnisotropyEnable(b8 enable) { anisotropyEnable = enable; return *this; }
		GfxSamplerDesc& setMaxAnisotropy(f32 max) { maxAnisotropy = max; return *this; }
		GfxSamplerDesc& setCompareEnable(b8 enable) { compareEnable = enable; return *this; }
		GfxSamplerDesc& setCompareOp(CompareOp op) { compareOp = op; return *this; }
		GfxSamplerDesc& setMinLod(f32 lod) { minLod = lod; return *this; }
		GfxSamplerDesc& setMaxLod(f32 lod) { maxLod = lod; return *this; }
		GfxSamplerDesc& setBorderColor(BorderColor color) { borderColor = color; return *this; }
	};

}
