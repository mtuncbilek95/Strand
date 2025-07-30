#include "DomainFilterProxy.h"

namespace Flax
{
	DomainFilterProxy::DomainFilterProxy(QObject* pParent)
	{
		m_excluded << "tmp" << "bin" << "obj" << "meta" << "odt";
	}

	bool DomainFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
	{
		QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

		if (!index.isValid())
			return true;

		QFileSystemModel* fsModel = qobject_cast<QFileSystemModel*>(sourceModel());
		if (!fsModel)
			return true;

		if (fsModel->isDir(index))
			return true;
		else
		{
			QString suffix = fsModel->fileInfo(index).suffix().toLower();
			if (m_excluded.contains(suffix))
				return false;
		}

		return true;
	}
}
