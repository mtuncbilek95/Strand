#include "RenderResolver.h"

#include <Runtime/Resource/Management/MeshManagement.h>
#include <Runtime/EntityComponent/Scene.h>
#include <Runtime/EntityComponent/Component/RenderComponent.h>

namespace Flax
{
    void RenderResolver::Resolve(Scene* scene)
    {
        entt::registry& enttReg = scene->GetRegistry();

        auto view = enttReg.view<RenderComponent>();
        
        for (auto& entity : view)
        {
            auto& comp = view.get<RenderComponent>(entity);

            auto mesh = m_meshManager->GetMeshResource(comp.m_meshId);
            auto material = m_meshManager->GetMaterialResource(comp.m_materialId);

            // Start Pass
            // SomeUnit->DrawIndex(mesh->GetIndexCount(), 0, 0, 0, 1);
            // End Pass
        }
    }
}