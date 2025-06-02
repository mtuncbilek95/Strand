/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Util/ImageFormat.h>
#include <Runtime/Graphics/RHI/Util/ShaderStage.h>

namespace Flax
{
	enum class VertexInputRate
	{
		Vertex = 0,
		Instance = 1
	};

	enum class PrimitiveTopology
	{
		PointList = 0,
		LineList = 1,
		LineStrip = 2,
		TriangleList = 3,
		TriangleStrip = 4,
		TriangleFan = 5,
		LineListAdj = 6,
		LineStripAdj = 7,
		TriangleListAdj = 8,
		TriangleStripAdj = 9
	};

	enum class DynamicState
	{
		Viewport = 1 << 0,
		Scissor = 1 << 1,
		PolygonMode = 1 << 2,
		PrimitiveTopology = 1 << 3,
	};

	enum class PolygonMode
	{
		Fill = 0,
		Line = 1,
		Point = 2
	};

	enum class CullMode
	{
		None = 0,
		Front = 1,
		Back = 2,
		FrontAndBack = 3,
	};

	enum class FaceOrientation
	{
		CW = 0,
		CCW = 1
	};

	enum class BlendFactor
	{
		Zero = 0,
		One = 1,
		SrcColor = 2,
		OneMinusSrcColor = 3,
		DstColor = 4,
		OneMinusDstColor = 5,
		SrcAlpha = 6,
		OneMinusSrcAlpha = 7,
		DstAplha = 8,
		OneMinusDstAlpha = 9,
		ConstantColor = 10,
		OneMinusConstantColor = 11,
		ConstantAlpha = 12,
		OneMinusConstantAlpha = 13,
		Src1Color = 14,
		OneMinusSrc1Color = 15,
		Src1Alpha = 16,
		OneMinusSrc1Alpha = 17
	};

	enum class BlendOp
	{
		Add = 0,
		Subtract = 1,
		ReverseSubtract = 2,
		Min = 3,
		Max
	};

	enum class CompareOp
	{
		Never = 0,
		Less = 1,
		Equal = 2,
		LesserEqual = 3,
		Greater = 4,
		NotEqual = 5,
		GreaterEqual = 6,
		Always = 7
	};

	enum class ColorComponent
	{
		Red = 1 << 0,
		Green = 1 << 1,
		Blue = 1 << 2,
		All = 0x3FFF
	};

	enum class LogicOp
	{
		Clear = 0,
		And = 1,
		AndReverse = 2,
		Copy = 3,
		AndInverted = 4,
		NoOp = 5,
		Xor = 6,
		Or = 7,
		Nor = 8,
		Equivalent = 9,
		Invert = 10,
		OrReverse = 11,
		CopyInverted = 12,
		OrInverted = 13,
		Nand = 14,
		Set = 15
	};

	enum class PipelineType
	{
		Graphics,
		Compute,
		Raytracing
	};

	struct Viewport
	{
		Math::Vec2f position = { 0.f, 0.f };
		Math::Vec2f size = { 0.f, 0.f };
		Math::Vec2f depth = { 0.f, 1.f };

		Viewport& setPosition(const Math::Vec2f pos) { position = pos; return *this; }
		Viewport& setSize(const Math::Vec2f sz) { size = sz; return *this; }
		Viewport& setDepth(const Math::Vec2f dp) { depth = dp; return *this; }
	};

	struct Scissor
	{
		Math::Vec2i offset = { 0, 0 };
		Math::Vec2u extent = { 0, 0 };

		Scissor& setOffset(const Math::Vec2i ofs) { offset = ofs; return *this; }
		Scissor& setExtent(const Math::Vec2u ext) { extent = ext; return *this; }
	};

	struct VertexInputBinding
	{
		u32 binding;
		u32 stride;
		VertexInputRate inputRate = VertexInputRate::Vertex;

		VertexInputBinding& setBinding(u32 bnd) { binding = bnd; return *this; }
		VertexInputBinding& setStride(u32 str) { stride = str; return *this; }
		VertexInputBinding& setBinding(VertexInputRate rate) { inputRate = rate; return *this; }
	};

	struct VertexInputAttribute
	{
		u32 location;
		u32 binding;
		ImageFormat format;
		u32 offset;

		VertexInputAttribute& setLocation(u32 loc) { location = loc; return *this; }
		VertexInputAttribute& setBindng(u32 bnd) { binding = bnd; return *this; }
		VertexInputAttribute& setFormat(ImageFormat frmt) { format = frmt; return *this; }
		VertexInputAttribute& setOffset(u32 ofs) { offset = ofs; return *this; }
	};

	struct PushConstantRange
	{
		ShaderStage stage;
		u32 offset;
		u32 sizeOfData;

		PushConstantRange& setStage(ShaderStage stg) { stage = stg; return *this; }
		PushConstantRange& setOffset(u32 ofs) { offset = ofs; return *this; }
		PushConstantRange& setSizeOfData(u32 size) { sizeOfData = size; return *this; }
	};

	struct PushConstants
	{
		Vector<PushConstantRange> ranges;

		PushConstants& addRange(const PushConstantRange& range) { ranges.push_back(range); return *this; }
	};

	struct InputBinding
	{
		VertexInputRate inputRate;
		Vector<ImageFormat> attrributes;

		InputBinding& setInputRate(VertexInputRate rate) { inputRate = rate; return *this; }
		InputBinding& addAttribute(ImageFormat format) { attrributes.push_back(format); return *this; }
	};

	struct InputAssembler
	{
		PrimitiveTopology topology;
		b8 primitiveRestart;
		Vector<InputBinding> bindings;

		InputAssembler& setTopology(PrimitiveTopology top) { topology = top; return *this; }
		InputAssembler& setPrimitiveRestart(b8 restart) { primitiveRestart = restart; return *this; }
		InputAssembler& addBinding(const InputBinding& binding) { bindings.push_back(binding); return *this; }
	};

	struct RasterizerState
	{
		b8 depthBiasEnable;
		f32 depthBiasConstantFactor;
		f32 depthBiasClamp;
		f32 depthBiasSlope;
		PolygonMode polygon;
		CullMode cull;
		FaceOrientation face;

		RasterizerState& setDepthBiasEnable(b8 enable) { depthBiasEnable = enable; return *this; }
		RasterizerState& setDepthBiasConstantFactor(f32 factor) { depthBiasConstantFactor = factor; return *this; }
		RasterizerState& setDepthBiasClamp(f32 clamp) { depthBiasClamp = clamp; return *this; }
		RasterizerState& setDepthBiasSlope(f32 slope) { depthBiasSlope = slope; return *this; }
		RasterizerState& setPolygonMode(PolygonMode mode) { polygon = mode; return *this; }
		RasterizerState& setCullMode(CullMode mode) { cull = mode; return *this; }
		RasterizerState& setFaceOrientation(FaceOrientation orientation) { face = orientation; return *this; }
	};

	struct BlendAttachment
	{
		b8 blendEnable;
		BlendFactor srcColor;
		BlendFactor dstColor;
		BlendOp colorOp;
		BlendFactor srcAlpha;
		BlendFactor dstAlpha;
		BlendOp alphaOp;
		ColorComponent colorMask;

		BlendAttachment& setBlendEnable(b8 enable) { blendEnable = enable; return *this; }
		BlendAttachment& setSrcColor(BlendFactor factor) { srcColor = factor; return *this; }
		BlendAttachment& setDstColor(BlendFactor factor) { dstColor = factor; return *this; }
		BlendAttachment& setColorOp(BlendOp op) { colorOp = op; return *this; }
		BlendAttachment& setSrcAlpha(BlendFactor factor) { srcAlpha = factor; return *this; }
		BlendAttachment& setDstAlpha(BlendFactor factor) { dstAlpha = factor; return *this; }
		BlendAttachment& setAlphaOp(BlendOp op) { alphaOp = op; return *this; }
		BlendAttachment& setColorMask(ColorComponent mask) { colorMask = mask; return *this; }
	};

	struct BlendState
	{
		b8 logicEnable;
		LogicOp logicOp;
		Vector<BlendAttachment> attachments;

		BlendState& setLogicEnable(b8 enable) { logicEnable = enable; return *this; }
		BlendState& setLogicOp(LogicOp op) { logicOp = op; return *this; }
		BlendState& addAttachment(const BlendAttachment& attachment) { attachments.push_back(attachment); return *this; }
	};

	struct DepthStencilState
	{
		b8 depthTestEnable;
		b8 depthWriteEnable;
		CompareOp depthOp;
		b8 depthBoundEnable;
		f32 minDepth;
		f32 maxDepth;

		DepthStencilState& setDepthTestEnable(b8 enable) { depthTestEnable = enable; return *this; }
		DepthStencilState& setDepthWriteEnable(b8 enable) { depthWriteEnable = enable; return *this; }
		DepthStencilState& setDepthOp(CompareOp op) { depthOp = op; return *this; }
		DepthStencilState& setDepthBoundEnable(b8 enable) { depthBoundEnable = enable; return *this; }
		DepthStencilState& setMinDepth(f32 min) { minDepth = min; return *this; }
		DepthStencilState& setMaxDepth(f32 max) { maxDepth = max; return *this; }
	};

	class GfxDescriptorLayout;
	class GfxShader;

	struct GfxGraphicsPipelineDesc
	{
		Vector<GfxDescriptorLayout*> layouts;
		Vector<GfxShader*> shaders;
		InputAssembler input;
		RasterizerState rasterizer;
		PushConstants pushes;
		BlendState blend;
		DepthStencilState depthStencil;

		GfxGraphicsPipelineDesc& addLayout(GfxDescriptorLayout* layout) { layouts.push_back(layout); return *this; }
		GfxGraphicsPipelineDesc& addShader(GfxShader* shader) { shaders.push_back(shader); return *this; }
	};

	struct GfxComputePipelineDesc
	{
	};

	struct GfxRaytracingPipelineDesc
	{
	};
}
