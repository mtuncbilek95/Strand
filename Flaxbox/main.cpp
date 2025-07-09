#include <Runtime/FileSystem/Service/VirtualFileService.h>
#include <Runtime/FileSystem/DiskFile/DiskFileSystem.h>

using namespace Flax;

int main()
{
	auto vfm = RuntimeService::Get<VirtualFileService>();

	vfm->Initialize(R"(C:\Users\mtunc\Desktop\TestFolder)");
	vfm->Mount("Assets", NewRef<DiskFileSystem>());
	vfm->Mount("Cache", NewRef<DiskFileSystem>());
	vfm->Mount("Content", NewRef<DiskFileSystem>());
	vfm->Mount("Intermediate", NewRef<DiskFileSystem>());

	if(vfm->Exists("Assets/TestFolder/Yalama/GrimLock.txt"))
		printf("File exists!\n");
	else
		printf("File does not exist!\n");

	vfm->Create("Intermediate/TestFolder/Grimlock/");

	return 0;
}