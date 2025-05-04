/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Containers/IObject.h>

#include <entt/entt.hpp>

namespace Flax
{
    class Entity;

    class Scene final : public IObject
    {
        typedef entt::registry EnTTRegistry;

    public:
        Scene(const String& name = "");
        ~Scene() override final;

    private:
        String m_sceneName;

        Vector<Ref<Entity>> m_entities;

    };
}