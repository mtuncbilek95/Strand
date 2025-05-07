/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/EntityComponent/Scene.h>

#include <entt/entt.hpp>

namespace Flax
{
    struct IComponentBase
    {
        virtual ~IComponentBase() = default;

        virtual String GetName() const = 0;
        virtual entt::id_type GetTypeId() const = 0;
    };

    template<typename T>
    struct Component : IComponentBase
    {
        static String StaticName() 
        {
            StringView fullName = entt::type_name<T>().value();

            usize pos = fullName.rfind("::");
            if (pos != StringView::npos)
                return String(fullName.substr(pos + 2));
            else
                return String(fullName);
        }

        static entt::id_type StaticTypeId() { return entt::type_id<T>().hash(); }

        String GetName() const override { return StaticName(); }
        entt::id_type GetTypeId() const override { return StaticTypeId(); }
    };

    class GlobalComponentResolver
    {
    public:
        using RegisterFunc = function<Owned<IComponentBase>()>;

        static void RegisterComponent(const String& compName, RegisterFunc fn) { GetList().insert({ compName, fn }); }
        static Owned<IComponentBase> CreateComponent(const String& compName)
        {
            auto it = GetList().find(compName);
            if (it != GetList().end())
                return it->second();

            Log::Error(LogType::ECS, "Component {} not found", compName);
            return nullptr;
        }
    private:
        static HashMap<String, RegisterFunc>& GetList() 
        {
            static HashMap<String, RegisterFunc> list;
            return list;
        }
    };
}