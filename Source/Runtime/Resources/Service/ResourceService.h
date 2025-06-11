/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/Cooked/Core/IResource.h>

namespace Flax
{
	class ResourceService : public RuntimeServiceBase
	{
	public:
		template<typename T, typename = std::enable_if<std::is_base_of_v<IResource, T>>>
		T* RegisterResource(const Any& args)
		{
			auto resourcePtr = GlobalResourceResolver::CreateResource(T::StaticType(), args);

			if (resourcePtr)
			{
				m_resources[T::StaticTypeId()].insert({ resourcePtr->GetId(), resourcePtr });
				Log::Debug(LogType::Resource, "Adding a resource {} to ResourceService with ID: {}", T::StaticType(), resourcePtr->GetId().ToString());
				return static_cast<T*>(resourcePtr.get());
			}
			else
				Log::Critical(LogType::Resource, "Could not register the resource typed as {}", T::StaticType());

			return nullptr;
		}
		void UnregisterResource(u64 hashId) {}
		void ResetServiceField() override final;

		template<typename T>
		T* GetResource(u64 hashId)
		{
			auto view = m_resources.find(T::StaticTypeId());
			if (view != m_resources.end())
			{
				auto it = view.find(hashId);

				if (it != view.end())
					return static_cast<T*>(it->second.get());
				else
					Log::Critical(LogType::Resource, "Resource with ID {} not found", hashId);

				return nullptr;
			}
			else
				Log::Critical(LogType::Resource, "ResourceTypeId {} not found", T::StaticTypeId());

			return nullptr;
		}

	private:
		HashMap<u64, HashMap<Uuid, Ref<IResource>, UuidHash>> m_resources; // <ResourceHashType, <ResourceUuid, Resource>>
	};
}