#include "OrbitCamera.h"

namespace Flax
{
    OrbitCamera::OrbitCamera(f32 fovDeg, f32 aspectRatio, f32 nearZ, f32 farZ) : m_configuration({ 20, -30, 50 }),
        m_viewMatrix(Math::identity<Math::Mat4f>()), m_projMatrix(Math::identity<Math::Mat4f>()), m_targetPosition({ 0, 0, 0 })
    {
        m_projMatrix = Math::perspective(Math::radians(fovDeg), aspectRatio, nearZ, farZ);
    }

    OrbitCamera::~OrbitCamera()
    {
    }

    void OrbitCamera::SetAzimuth(f32 azimuth)
    {
        m_configuration.x += azimuth;
    }

    void OrbitCamera::SetElevation(f32 elevation)
    {
        m_configuration.y += elevation;
        f32 epsilon = 0.0001f;
        m_configuration.y = Math::clamp(m_configuration.y, -90.f + epsilon, 90.f - epsilon);
    }

    void OrbitCamera::SetDistance(f32 distance)
    {
        m_configuration.z += distance;
        m_configuration.z = Math::clamp(m_configuration.z, 5.f, 200.f);
    }

    void OrbitCamera::Dolly(const Math::Vec2f& delta)
    {
        Math::Vec3f pos = GetPosition();

        Math::Vec3f zaxis = Math::normalize(pos - m_targetPosition);
        Math::Vec3f xaxis = Math::normalize(Math::cross(Math::Vec3f(0, 1, 0), zaxis));
        Math::Vec3f yaxis = Math::normalize(Math::cross(zaxis, xaxis));

        m_targetPosition += xaxis * delta.x + yaxis * delta.y;
    }

    Math::Vec3f OrbitCamera::GetPosition() const
    {
        f32 x = m_configuration.z * std::cos(m_configuration.y * Math::Pi / 180) * std::sin(m_configuration.x * Math::Pi / 180);
        f32 y = m_configuration.z * std::sin(m_configuration.y * Math::Pi / 180);
        f32 z = m_configuration.z * std::cos(m_configuration.y * Math::Pi / 180) * std::cos(m_configuration.x * Math::Pi / 180);

        return Math::Vec3f(x, y, z) + m_targetPosition;
    }

    const Math::Mat4f& OrbitCamera::GetViewMatrix()
    {
        Math::Vec3f pos = GetPosition();
        m_viewMatrix = Math::lookAt(pos, m_targetPosition, Math::Vec3f(0.f, 1.f, 0.f));
        return m_viewMatrix;
    }

    void OrbitCamera::UpdateProjetionMatrix(f32 fovY, f32 aspectRatio, f32 nZ, f32 fZ)
    {
        m_projMatrix = Math::perspective(Math::radians(fovY), aspectRatio, nZ, fZ);
    }
}