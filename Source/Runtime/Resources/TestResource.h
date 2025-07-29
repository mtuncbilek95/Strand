/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Resources/ResourceBase.h>

namespace Flax
{
	class TestResource : public ResourceBase
	{
		FLAX_OBJECT(TestResource)
	public:
		TestResource();
		~TestResource();

	private:
		String m_newFuckery = "TestResource";
	};

	class ResourceOne : public TestResource
	{
		FLAX_OBJECT(ResourceOne)
	public:
		ResourceOne() = default;
		~ResourceOne() = default;

	private:
		u64 m_oneU64 = 25;
	};

	class ResourceTwo : public ResourceOne
	{
		FLAX_OBJECT(ResourceTwo)
	public:
		ResourceTwo() = default;
		~ResourceTwo() = default;

	private:
		u64 m_twoU64 = 1;
	};

	class ResourceThree : public ResourceBase
	{
		FLAX_OBJECT(ResourceThree)
	public:
		ResourceThree() = default;
		~ResourceThree() = default;

	private:
		u64 m_threeU64 = 12;
	};
}
