#include "NoExtensionDelegate.h"

namespace Flax
{
	NoExtensionDelegate::NoExtensionDelegate(QObject* pParent) : QStyledItemDelegate(pParent)
	{
	}

	QString NoExtensionDelegate::displayText(const QVariant& value, const QLocale& locale) const
	{
		QString text = value.toString();
		QFileInfo fileInfo(text);

		if (fileInfo.isFile())
			return fileInfo.baseName();

		return text;
	}
}
