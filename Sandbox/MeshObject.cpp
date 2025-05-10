#include "MeshObject.h"

#include <Runtime/Vulkan/Buffer/VBuffer.h>
#include <Runtime/Vulkan/Queue/VQueue.h>
#include <Runtime/Vulkan/Command/VCmdBuffer.h>
#include <Runtime/Vulkan/Command/VCmdPool.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Sync/VSemaphore.h>
#include <Runtime/Vulkan/Sync/VFence.h>

#include <Runtime/Resource/Importer/MeshImporter.h>

namespace Flax
{
    MeshObject::MeshObject()
    {
    }

    MeshObject::~MeshObject()
    {
    }

    void MeshObject::Load(const String& path, VQueue* tQueue, VDevice* pDevice)
    {
        std::thread testThread([this, tQueue, pDevice]()
            {
                Geometry data = MeshImporter::ReadGeometry(R"(D:\Projects\glTF-Sample-Models\2.0\SciFiHelmet\glTF\SciFiHelmet.gltf)");

                BufferProps bufferProps =
                {
                    .sizeInBytes = data.GetVertexCount() * sizeof(Vertex) + data.GetIndexCount() * sizeof(u32),
                    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                    .memUsage = VMA_MEMORY_USAGE_CPU_ONLY,
                    .allocFlags = 0
                };
                VBuffer stage(bufferProps, pDevice);

                stage.Update(data.GenerateRawVertex(VertexRawDataFlags::All | ~VertexRawDataFlags::Color));
                stage.Update(data.GenerateRawIndex(), data.GetVertexCount() * sizeof(Vertex));

                BufferProps gpuBufferProps =
                {
                    .sizeInBytes = stage.GetTotalSize(),
                    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                    .memUsage = VMA_MEMORY_USAGE_GPU_ONLY,
                    .allocFlags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT
                };
                m_GpuBuffer = MakeShared<VBuffer>(gpuBufferProps, pDevice);

                CmdPoolProps cmdPoolProps =
                {
                    .queue = tQueue,
                    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
                };
                VCmdPool cmdPool(cmdPoolProps, pDevice);
                auto cmdBuffer = cmdPool.CreateCmdBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

                cmdBuffer->BeginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
                cmdBuffer->CopyStageToBuffer(&stage, &*m_GpuBuffer, CopyBufferProps());
                cmdBuffer->EndRecord();

                VFence vkTransferFence(false, pDevice);
                tQueue->Submit({ &*cmdBuffer }, {}, {}, &vkTransferFence, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);

                vkTransferFence.Wait();
                vkTransferFence.Reset();
            });

        testThread.detach();
    }

    void MeshObject::Unload()
    {
        if (m_GpuBuffer)
            m_GpuBuffer.reset();
    }
}
