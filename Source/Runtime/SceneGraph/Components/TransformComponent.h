/*
 * Licensed under the terms specified in the LICENSE.md file
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/SceneGraph/IComponent.h>

namespace Strand
{
	STRAND_CLASS();
	class TransformComponent : public IComponent
	{
		STRAND_OBJECT(TransformComponent);
	public:
		TransformComponent();
		~TransformComponent() = default;

		void SetPosition(const Math::Vec3f& position) { m_position = position; }
		void SetRotation(const Math::Vec3f& rotation) { m_rotation = rotation; }
		void SetScale(const Math::Vec3f& scale) { m_scale = scale; }

		const Math::Vec3f& GetPosition() const { return m_position; }
		const Math::Vec3f& GetRotation() const { return m_rotation; }
		const Math::Vec3f& GetScale() const { return m_scale; }

	private:
		STRAND_FIELD();
		Math::Vec3f m_position;
		STRAND_FIELD();
		Math::Vec3f m_rotation;
		STRAND_FIELD();
		Math::Vec3f m_scale;
	};
}