#include <Runtime/VirtualFile/VirtualFileSystem.h>

using namespace Flax;

int main()
{
	VirtualFileSystem vfs(VFSType::Editor, "D:/Projects/PythonQtTest");

	vfs.AddNode("FirstLayer_A", VFSNodeType::Directory);
	vfs.AddNode("FirstLayer_B", VFSNodeType::Directory);
	vfs.AddNode("FirstLayer_C", VFSNodeType::Directory);
	vfs.AddNode("FirstLayer_D", VFSNodeType::Directory);

	auto* nodeB = vfs.FindNode("FirstLayer_B");

	vfs.AddNode("SecondLayer_A", VFSNodeType::Directory, nodeB);
	vfs.AddNode("SecondLayer_B", VFSNodeType::Directory, nodeB);
	vfs.AddNode("SecondLayer_C", VFSNodeType::Directory, nodeB);
	vfs.AddNode("SecondLayer_D", VFSNodeType::Directory, nodeB);
	vfs.AddNode("SecondLayer_E", VFSNodeType::Directory, nodeB);

	auto* nodeD = vfs.FindNode("SecondLayer_D", nodeB);

	vfs.AddNode("ThirdLayer_A", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_B", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_C", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_D", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_E", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_F", VFSNodeType::Directory, nodeD);
	vfs.AddNode("ThirdLayer_G", VFSNodeType::Directory, nodeD);

	Log::Warn(LogType::Asset, "Testing folder search: {}", vfs.AbsolutePath("ThirdLayer_F"));
}