#include "ShaderCompiler.h"

#include <Runtime/Data/Tools/DataReader.h>

#include <shaderc/shaderc.hpp>
#include <magic_enum.hpp>

namespace Flax
{
	void ShaderAssert(shaderc_compilation_status status, const String& title, const String& message)
	{
		if (status != shaderc_compilation_status_success)
		{
			Log::Critical(LogType::ShaderCompiler, "[{0}:{1}] - {2}", title, magic_enum::enum_name(status), message);
			exit(-1);
		}
	}

	class ShaderIncluder : public shaderc::CompileOptions::IncluderInterface
	{
		struct IncludeData
		{
			shaderc_include_result result = {};
			String m_fullPath;
			ReadArray<c8> m_content;
		};

	public:
		ShaderIncluder(const String& path);
		~ShaderIncluder() override = default;

		shaderc_include_result* GetInclude(const char* requestedSource, shaderc_include_type type, const char* requestingSource, u64 includeDepth) override;
		void ReleaseInclude(shaderc_include_result* data) override;

	private:
		String ResolveInclude(const String& requestedSource) const;
		String m_includePath;
	};

	shaderc_shader_kind CheckStage(const String& extensionName)
	{
		static Map<String, shaderc_shader_kind> stageMap = {
			{ "vert", shaderc_glsl_vertex_shader },       { "frag", shaderc_glsl_fragment_shader },
			{ "comp", shaderc_glsl_compute_shader },      { "geom", shaderc_glsl_geometry_shader },
			{ "tesc", shaderc_glsl_tess_control_shader }, { "tese", shaderc_glsl_tess_evaluation_shader },
			{ "rgen", shaderc_glsl_raygen_shader },       { "rint", shaderc_glsl_intersection_shader },
			{ "rahit", shaderc_glsl_anyhit_shader },      { "rchit", shaderc_glsl_closesthit_shader },
			{ "rmiss", shaderc_glsl_miss_shader },        { "rcall", shaderc_glsl_callable_shader },
			{ "task", shaderc_glsl_task_shader },         { "mesh", shaderc_glsl_mesh_shader }
		};

		auto it = stageMap.find(extensionName);
		if (it != stageMap.end())
			return it->second;
		else
			Log::Critical(LogType::ShaderCompiler, "Failed to find shader stage for extension '{}'", extensionName);

		return shaderc_glsl_vertex_shader;
	}

	ShaderIncluder::ShaderIncluder(const String& path) : m_includePath(path)
	{
	}

	shaderc_include_result* ShaderIncluder::GetInclude(const char* requestedSource, shaderc_include_type type, const char* requestingSource, u64 includeDepth)
	{
		IncludeData* includeData = new IncludeData();
		includeData->m_fullPath = ResolveInclude(requestedSource);

		// Do not null terminate the string
		includeData->m_content = DataReader::ReadData(m_includePath, false, false);

		shaderc_include_result* result = &includeData->result;
		result->content = includeData->m_content.Data();
		result->content_length = includeData->m_content.Size();
		result->source_name = includeData->m_fullPath.data();
		result->source_name_length = includeData->m_fullPath.size();
		result->user_data = includeData;

		return result;
	}

	void ShaderIncluder::ReleaseInclude(shaderc_include_result* data)
	{
		delete static_cast<IncludeData*>(data->user_data);
	}

	String ShaderIncluder::ResolveInclude(const String& requestedSource) const
	{
		String path = m_includePath + requestedSource;

		if (std::filesystem::exists(path))
			return path;
		else
			throw std::runtime_error("Failed to resolve include '" + requestedSource + "'!");
	}

	ReadArray<u32> ShaderCompiler::CompileShader(const String& shaderPath, const String& includePath, const String& entryPoint)
	{
		ReadArray<c8> file = DataReader::ReadData(shaderPath, false, true);

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetSourceLanguage(shaderc_source_language_glsl);
		options.SetSuppressWarnings();
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
		options.SetTargetSpirv(shaderc_spirv_version_1_6);

		if (!includePath.empty())
			options.SetIncluder(std::make_unique<ShaderIncluder>(includePath));

		auto extensionSplit = shaderPath.rfind('.');
		if (extensionSplit == String::npos)
			Log::Critical(LogType::ShaderCompiler, "Failed to find extension for shader '{}'", shaderPath);

		auto stage = CheckStage(shaderPath.substr(extensionSplit + 1));

		shaderc::PreprocessedSourceCompilationResult preResult = compiler.PreprocessGlsl(file.Data(), stage, "", options);
		ShaderAssert(preResult.GetCompilationStatus(), "PreResult", preResult.GetErrorMessage());

		shaderc::SpvCompilationResult compResult = compiler.CompileGlslToSpv(preResult.begin(), stage, "", options);
		ShaderAssert(compResult.GetCompilationStatus(), "CompilationResult", compResult.GetErrorMessage());

		ReadArray<u32> returnResult(compResult.cend() - compResult.cbegin());
		// Copy the data to the return array
		std::copy(compResult.begin(), compResult.end(), returnResult.Data());

		return returnResult;
	}
}