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

    struct VPStruct
    {
        Math::Mat4f viewMatrix;
        Math::Mat4f projMatrix;
    };

    class MeshObject
    {
    public:
        MeshObject(VDevice* pDevice);
        ~MeshObject();

        // Test for loading during runtime
        void Load(const String& path, VQueue* tQueue, VDevice* pDevice, Mutex* mutex);
        // Test for killing during runtime
        void Unload();

        b8 IsReady() const { return m_isReady; }
        usize GetIndexCount() const { return m_indexCount; }
        usize GetVertexCount() const { return m_vertexCount; }
        usize GetIndexOffset() const { return m_indexOffset; }

        VBuffer* GetGpuBuffer() const { return m_GpuBuffer.get(); }
        VBuffer* GetModelBuffer() const { return m_modelBuffer.get(); }
        VBuffer* GetVPBuffer() const { return m_vpBuffer.get(); }

    private:
        Ref<VBuffer> m_GpuBuffer;
        Ref<VBuffer> m_modelBuffer;
        Ref<VBuffer> m_vpBuffer;

        Math::Mat4f m_modelMatrix;
        VPStruct m_vpStruct;

        usize m_indexCount = 0;
        usize m_vertexCount = 0;
        usize m_indexOffset = 0;
        b8 m_isReady = false;
    };
}