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
	class DomainPathView : public QWidget
	{
		Q_OBJECT
	public:
		DomainPathView(QWidget* pParent = nullptr);
		~DomainPathView();

	signals:
		void onPathViewClicked(const QString& path);

	public slots:
		void refreshPathView(const QString& path);

	private:
		void clearLayout();
	};
}
