/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Editor/Core/CoreMinimal.h>


namespace Strand
{
	class DomainIconProvider : public QFileIconProvider
	{
	public:
		DomainIconProvider();
		~DomainIconProvider();

		void setIcons();
		QIcon icon(const QFileInfo& info) const override final;

	private:
		HashMap<String, QIcon> m_icons;
	};
}
