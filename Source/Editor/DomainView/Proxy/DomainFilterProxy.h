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
	class DomainFilterProxy : public QSortFilterProxyModel
	{
		Q_OBJECT;
	public:
		DomainFilterProxy(QObject* pParent = nullptr);
		~DomainFilterProxy() override = default;

	protected:
		bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override final;

	private:
		QStringList m_excluded;
	};
}
