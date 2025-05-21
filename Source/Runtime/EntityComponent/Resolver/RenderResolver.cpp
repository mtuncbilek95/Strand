#include "RenderResolver.h"

#include <Runtime/Renderer/Renderer.h>

#include <Runtime/Vulkan/Command/VCmdBuffer.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>

#include <Runtime/Resource/Management/MeshManagement.h>
#include <Runtime/Resource/MaterialResource.h>

#include <Runtime/EntityComponent/Scene.h>
#include <Runtime/EntityComponent/Component/RenderComponent.h>


namespace Flax
{
    RenderResolver::RenderResolver(Renderer* usedRenderer) : m_renderer(usedRenderer)
    {
        CmdPoolProps vkGPoolProp =
        {
            .queue = usedRenderer->GetGraphicsQueue()
        };
        m_secondaryPool = NewRef<VCmdPool>(vkGPoolProp, usedRenderer->GetDevice());
        m_secondaryBuffer = m_secondaryPool->CreateCmdBuffer(VK_COMMAND_BUFFER_LEVEL_SECONDARY);
    }

    void RenderResolver::Resolve(Scene* scene)
    {
        if (!scene)
        {
            Log::Critical(LogType::Executor, "There is no scene in the RenderExecutor!");
            return;
        }

        entt::registry& enttReg = scene->GetRegistry();

        auto view = enttReg.view<RenderComponent>();
        
        for (auto& entity : view)
        {
            auto& comp = view.get<RenderComponent>(entity);

            auto mesh = m_meshManager->GetMeshResource(comp.m_meshId);
            auto material = m_meshManager->GetMaterialResource(comp.m_materialId);

            InheritanceProps inheritProp =
            {
                .renderPass = m_renderer->GetMainPass(),
                .framebuffer = nullptr,
                .subpass = 0
            };

            m_secondaryBuffer->BeginRecord(inheritProp, VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT);
            m_secondaryBuffer->EndRecord();
        }
    }
}