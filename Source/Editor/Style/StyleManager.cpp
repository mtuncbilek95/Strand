#include "StyleManager.h"

namespace Flax
{
	StyleManager::StyleManager()
	{
	}

	StyleManager::~StyleManager()
	{
	}

	QString StyleManager::LoadStyle()
	{
		QString style;

		const QString root = ":/Styles";

		QDir rootDir(root);
		QFileInfoList files = rootDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

		for (const QFileInfo& fileInfo : files)
		{
			QFile file(fileInfo.absoluteFilePath());
			if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				QTextStream in(&file);
				style.append(in.readAll());
			}
		}

		QDirIterator it(root, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

		while (it.hasNext())
		{
			QString subDirPath = it.next();
			QDir subDir(subDirPath);

			QFileInfoList subFiles = subDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

			for (const QFileInfo& fileInfo : subFiles)
			{
				QFile file(fileInfo.absoluteFilePath());
				if (file.open(QIODevice::ReadOnly | QIODevice::Text))
				{
					QTextStream in(&file);
					style.append(in.readAll());
				}
			}
		}

		return style;
	}

	QStringList StyleManager::LoadFontFamilies() const
	{
		QStringList loadedFontFamilies;

		QDirIterator it(":/Fonts", QDirIterator::Subdirectories);
		while (it.hasNext())
		{
			const QString path = it.next();
			if (path.endsWith(".ttf", Qt::CaseInsensitive))
			{
				i32 fontId = QFontDatabase::addApplicationFont(path);
				if (fontId != -1)
				{
					QStringList families = QFontDatabase::applicationFontFamilies(fontId);
					for (const QString& fam : families)
						loadedFontFamilies.append(fam);
				}
				else
					Log::Critical(LogType::Editor, "Failed to load font from >> {}", path.toStdString().data());
			}
		}

		return loadedFontFamilies;
	}
}