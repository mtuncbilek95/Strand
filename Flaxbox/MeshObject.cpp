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
	MeshObject::MeshObject() : m_isReady(false)
	{
	}

	MeshObject::~MeshObject()
	{
	}

	void MeshObject::Load(const String& path, VQueue* tQueue, VDevice* pDevice)
	{
		m_modelMatrix = Math::identity<Math::Mat4f>();
		m_vpStruct.viewMatrix = Math::identity<Math::Mat4f>();
		m_vpStruct.projMatrix = Math::identity<Math::Mat4f>();

		m_vpStruct.viewMatrix = Math::lookAt(
			Math::Vec3f(0.0f, 0.0f, 5.f),
			Math::Vec3f(0.0f, 0.0f, 0.0f),
			Math::Vec3f(0.0f, -1.0f, 0.0f)
		);
		m_vpStruct.projMatrix = Math::perspective(Math::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);

		BufferProps modelProp =
		{
			.sizeInBytes = sizeof(Math::Mat4f),
			.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
			.allocFlags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT
		};
		m_modelBuffer = NewRef<VBuffer>(modelProp, pDevice);
		m_modelBuffer->Update(&m_modelMatrix, sizeof(Math::Mat4f));

		BufferProps vpProp =
		{
			.sizeInBytes = sizeof(VPStruct),
			.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
			.allocFlags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT
		};
		m_vpBuffer = NewRef<VBuffer>(vpProp, pDevice);
		m_vpBuffer->Update(&m_vpStruct, sizeof(VPStruct));

		Geometry data = MeshImporter::ReadGeometry(path);

		m_vertexCount = data.GetVertexCount();

		BufferProps bufferProps =
		{
			.sizeInBytes = data.GetVertexCount() * sizeof(Vertex),
			.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
			.allocFlags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT
		};

		VBuffer stage(bufferProps, pDevice);

		stage.Update(data.GenerateRawVertex(VertexRawDataFlags::All));

		BufferProps gpuBufferProps =
		{
			.sizeInBytes = stage.GetTotalSize(),
			.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			.memUsage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
			.allocFlags = 0
		};
		m_GpuBuffer = NewRef<VBuffer>(gpuBufferProps, pDevice);

		CmdPoolProps cmdPoolProps =
		{
			.queue = tQueue,
			.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
		};
		VCmdPool cmdPool(cmdPoolProps, pDevice);
		auto cmdBuffer = cmdPool.CreateCmdBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

		cmdBuffer->BeginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
		cmdBuffer->CopyStageToBuffer({ &stage, m_GpuBuffer.get(), 0, (u32)m_GpuBuffer->GetOffset(), (u32)stage.GetSizeInBytes() });
		cmdBuffer->EndRecord();

		VFence vkTransferFence(false, pDevice);

		tQueue->Submit({ &*cmdBuffer }, {}, {}, &vkTransferFence, VK_PIPELINE_STAGE_TRANSFER_BIT);

		vkTransferFence.Wait();
		vkTransferFence.Reset();
	}

	void MeshObject::Unload()
	{
		if (m_GpuBuffer)
			m_GpuBuffer.reset();
	}
}