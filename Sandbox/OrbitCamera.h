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
    class OrbitCamera final
    {
    public:
        OrbitCamera(f32 fovDeg = 40.f, f32 aspectRatio = 1920.f / 1080.f, f32 nearZ = .1f, f32 farZ = 1000.f);
        ~OrbitCamera();

        void SetAzimuth(f32 azimuth);
        void SetElevation(f32 elevation);
        void SetDistance(f32 distance);
        void Dolly(const Math::Vec2f& delta);

        Math::Vec3f GetPosition() const;
        const Math::Mat4f& GetViewMatrix();
        const Math::Mat4f& GetProjectionMatrix() { return m_projMatrix; }

        f32 GetAzimuth() const { return m_configuration.x; }
        f32 GetElevation() const { return m_configuration.y; }
        f32 GetDistance() const { return m_configuration.z; }

        void UpdateProjetionMatrix(f32 fovY, f32 aspectRatio, f32 nZ, f32 fZ);

    private:
        Math::Vec3f m_targetPosition;

        Math::Mat4f m_viewMatrix;
        Math::Mat4f m_projMatrix;

        Math::Vec3f m_configuration;
    };
}