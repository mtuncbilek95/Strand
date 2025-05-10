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
    class VDevice;
    class VBuffer;
    class VQueue;

    class MeshObject
    {
    public:
        MeshObject();
        ~MeshObject();

        // Test for loading during runtime
        void Load(const String& path, VQueue* tQueue, VDevice* pDevice);
        // Test for killing during runtime
        void Unload();

    private:
        Ref<VBuffer> m_GpuBuffer;
    };
}