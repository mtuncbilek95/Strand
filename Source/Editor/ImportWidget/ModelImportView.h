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
	class ModelImportView : public QDialog
	{
		Q_OBJECT
	public:
		ModelImportView(QWidget* pParent = nullptr);
		~ModelImportView();

	private:
	};
}
