#include <Runtime/Resources/Asset/Core/ImporterRegistry.h>
#include <Runtime/Resources/Asset/Core/MetadataRegistry.h>

#include <Runtime/Resources/Asset/Texture/TextureImporter.h>
#include <Runtime/Resources/Asset/Texture/TextureMetadata.h>
#include <Runtime/Thread/ThreadPool.h>

using namespace Flax;

int main()
{
	ThreadPool testpool(8);

	for (;;)
	{
		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test1.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test2.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test3.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test4.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test5.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test6.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		testpool.EnqueueJob([]()
			{
				auto& importInfo = ImporterRegistry::Get().ImportType<TextureImporter>();
				auto importer = importInfo.createInstance();

				auto& metaInfo = MetadataRegistry::Get().MetaType<TextureMetadata>();
				auto meta = metaInfo.createInstance();
				importer->Import(R"(C:\Users\mtunc\Pictures\Screenshots\Test7.png)", *meta);

				Log::Debug(LogType::Asset, "Name: {}, Path: {}, Uuid: {}", meta->assetName, meta->assetPath, meta->assetId.ToString());
			});

		_sleep(50);
	}
}