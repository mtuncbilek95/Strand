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
	class IResource
	{
	public:
		IResource();
		virtual ~IResource() = default;

		virtual String GetType() = 0;
		virtual u64 GetTypeId() = 0;
		const Uuid& GetId() const { return m_uuid; }

	private:
		Uuid m_uuid;
	};

	template<typename T>
	class ResourceBase : public IResource
	{
	public:
		static String StaticType()
		{
			String fullName = TypeUtil::TypeName<T>();

			usize pos = fullName.rfind("::");
			if (pos != StringView::npos)
				return String(fullName.substr(pos + 2));
			else
				return String(fullName);
		}

		static u64 StaticTypeId() { return TypeUtil::GetTypeHash<T>(); }
		String GetType() override final { return StaticType(); }
		u64 GetTypeId() override final { return StaticTypeId(); }
	};

	class GlobalResourceResolver
	{
	public:
		using RegisterFunc = function<Ref<IResource>(const Any&)>;

		static void RegisterResource(const String& sourceName, RegisterFunc fn) { GetList().insert({ sourceName, fn }); }

		static Ref<IResource> CreateResource(const String& sourceName, const Any& args)
		{
			auto it = GetList().find(sourceName);
			if (it != GetList().end())
			{
				Log::Debug(LogType::Resource, "Found ResourceType {}", sourceName);
				return it->second(args);
			}

			Log::Error(LogType::Resource, "Resource {} not found", sourceName);
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