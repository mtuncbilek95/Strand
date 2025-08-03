#include "ResourceBase.h"

namespace Strand
{
	ResourceBase::ResourceBase(const ResourceDesc& desc) : m_resourceId(desc.resourceId), 
		m_resourceName(desc.resourceName), m_relativePath(desc.relativePath)
	{
	}

	ResourceBase::~ResourceBase()
	{
	}

}