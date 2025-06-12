#include "SceneWidget.h"

#include <Editor/HierarchyWidget/HierarchyService.h>
#include <Editor/Models/Hierarchy/HierarchyItemModel.h>

namespace Flax
{
	SceneWidget::SceneWidget(QWidget* pParent) : QWidget(pParent), m_ctx(&GfxContext::Get())
	{
		GfxContextDesc contextDesc = GfxContextDesc().setAPIType(GfxType::Vulkan)
			.setAppName("Flaxbox")
			.setAppVersion({ 1, 0, 0 })
			.setColorFormat(ImageFormat::R8G8B8A8_UNorm)
			.setImageCount(2)
			.setGraphicsQueueCount(1)
			.setComputeQueueCount(1)
			.setTransferQueueCount(1)
			.setDepthFormat(ImageFormat::D32_SFloat)
			.setPresentMode(PresentMode::Fifo)
			.setWindowSize({ u32(width()), u32(height()) })
			.setWindowHandle(reinterpret_cast<void*>(winId()));

		m_ctx->CreateContext(contextDesc);
	}

	SceneWidget::~SceneWidget()
	{
		m_ctx->DestroyContext();
	}

	void SceneWidget::resizeEvent(QResizeEvent* event)
	{
		m_ctx->DispatchResize({ u32(event->size().width()), u32(event->size().height()) });
	}

	void SceneWidget::RunScene()
	{
		m_ctx->BeginFrame();
		// m_ctx->DispatchSubmission();
		m_ctx->EndFrame();

		QMetaObject::invokeMethod(this, "RunScene", Qt::QueuedConnection);
	}
}
