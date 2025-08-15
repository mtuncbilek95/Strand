#include "SceneResource.h"

namespace Strand
{
	SceneResource::SceneResource(const ResourceDesc& desc, const String& sceneName) : ResourceBase(desc), 
		m_sceneName(sceneName)
	{
	}

	SceneResource::~SceneResource()
	{
	}
}