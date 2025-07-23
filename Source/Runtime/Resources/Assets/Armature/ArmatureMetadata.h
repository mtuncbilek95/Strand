/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Assets/AssetMetadata.h>

namespace Flax
{
	struct ArmatureJoint
	{
		String jointName;
		i32 parentIndex = -1;
		Math::Vec3f localPosition;
		Math::Quatf localRotation;
		Math::Vec3f localScale;
		f32 length;

		void Serialize(Toml& tomlOut) const;
		void Deserialize(const Toml& tomlIn);
	};

	struct ArmatureMetaExtension : public IAssetMetaExtension
	{
		u32 boneCount;
		Vector<ArmatureJoint> bones;
		Vector<i32> rootBoneIndices;
		u32 maxHierarchyDepth;

		u32 maxInfluencesPerVertex;
		f32 complexityScore;
		usize memoryFootprintBytes;

		b8 hasConsistentBoneOrientation;
		b8 hasUniformScale;
		b8 hasGimbalLockRisk;

		b8 optimizeHierarchy;
		b8 removeUnusedBones;
		f32 scaleMultiplier;

		void Serialize(Toml& tomlOut) override final;
		void Deserialize(const Toml& tomlIn) override final;

	protected:
		void InfoInternal(const Path& assetPath) override final;
	};
}
