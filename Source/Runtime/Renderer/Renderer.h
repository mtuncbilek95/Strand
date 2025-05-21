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
	class VInstance;
	class VDevice;
	class VSwapchain;
	class VQueue;
	class VCmdPool;
	class VCmdBuffer;
	class VSemaphore;
	class VFence;
	class VImage;
	class VImageView;
	class VRenderPass;
	class VFramebuffer;

	struct RendererProps final
	{
		Math::Vec2u rendererSize;
		void* windowHandle;
	};

	class Renderer
	{
	public:
		Renderer(const RendererProps& desc);
		~Renderer();

		void Run(const Vector<VCmdBuffer*>& buffers);
		void Stop();

		VRenderPass* TempPass() const { return m_presentPass.get(); }
		VFramebuffer* TempFBO() const { return m_presentFBO.get(); }
		VQueue* TempGraphics() const { return m_vkGraphicsQueue.get(); }
		VQueue* TempTransfer() const { return m_vkTransferQueue.get(); }
		VDevice* TempDevice() const { return m_vkDevice.get(); }

	private:
		Ref<VInstance> m_vkInstance;
		Ref<VDevice> m_vkDevice;
		Ref<VSwapchain> m_vkSwapchain;

		Ref<VQueue> m_vkGraphicsQueue;
		Ref<VQueue> m_vkTransferQueue;

		Ref<VCmdPool> m_executionCmdPool;
		Vector<Ref<VCmdBuffer>> m_executionCmdBuffers;

		Vector<Ref<VSemaphore>> m_renderSemaphores;
		Ref<VFence> m_renderFence;
		Ref<VFence> m_transferFence;

		Ref<VImage> m_depthImage;
		Ref<VImageView> m_depthView;

		Ref<VRenderPass> m_presentPass;
		Ref<VFramebuffer> m_presentFBO;
	};
}
