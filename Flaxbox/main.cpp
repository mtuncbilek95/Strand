#include <Runtime/FileSystem/FileSystem.h>

using namespace Flax;

int main()
{
	auto fs = RuntimeService::Get<FileSystem>();

	fs->SetRootPath(R"(D:\)");
	auto path = fs->SeparatePathFromRoot(R"(D:\Projects\FlaxTestProject\TestProject.toml)");

	printf("%s\n", path.string().data());
}