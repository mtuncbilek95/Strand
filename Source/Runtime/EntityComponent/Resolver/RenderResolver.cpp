#include "RenderResolver.h"

#include <Runtime/EntityComponent/Scene.h>

namespace Flax
{
    void RenderResolver::Resolve(Scene* scene)
    {
        
        scene->GetRegistry().view<RenderComponent>(); 

        // sorted
        for(auto entity : scene->GetRegistry().view<RenderComponent>().each())
        {
            auto& renderComponent = scene->GetRegistry().get<RenderComponent>(entity);
            if (renderComponent.IsVisible())
            {
                switch (type)
                {
                    case Type::Opaque:
                        RenderGraph->BeginPass("Opaque");
                        Doyourthing();
                        RenderGraph->EndPass();
						break;
                }
                RenderGraph->BeginPass()
            }
		}
    }
}