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
	class StyleManager final : public Singleton<StyleManager>
	{
	public:
		StyleManager() = default;

		QString LoadStyle();
		QStringList LoadFontFamilies() const;

	private:
		QList<QFile> m_styles = {};
	};
}