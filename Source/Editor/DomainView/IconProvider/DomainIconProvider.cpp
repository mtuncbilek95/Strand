#include "DomainIconProvider.h"

namespace Flax
{
	DomainIconProvider::DomainIconProvider()
	{
		
	}

	DomainIconProvider::~DomainIconProvider()
	{
	}

	void DomainIconProvider::setIcons()
	{
		m_icons["folder"] = QIcon(":/Icons/ContentBrowser/PB_Folder.svg");
		m_icons["file"] = QIcon(":/Icons/ContentBrowser/PB_File.svg");
		m_icons["scene"] = QIcon(":/Icons/ContentBrowser/PB_Scene.svg");
		m_icons["jpg"] = QIcon(":/Icons/ContentBrowser/PB_Texture.svg");
		m_icons["png"] = QIcon(":/Icons/ContentBrowser/PB_Texture.svg");
		m_icons["tga"] = QIcon(":/Icons/ContentBrowser/PB_Texture.svg");
		m_icons["gltf"] = QIcon(":/Icons/ContentBrowser/PB_Mesh.svg");
	}

	QIcon DomainIconProvider::icon(const QFileInfo& info) const
	{
		if(info.isDir())
			return m_icons.at("folder");
		else
		{
			QString suffix = info.suffix().toLower();

			auto it = m_icons.find(suffix.toStdString());
			if (it != m_icons.end())
				return it->second;
		}

		return QFileIconProvider::icon(info);
	}
}
