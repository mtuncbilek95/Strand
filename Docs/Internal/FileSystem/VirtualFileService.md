# File System

File system is a service object for engine to control the files inside of the project or game. The usage works like 
[The Example](./Service.md). 

## Functions

### ` void VirtualFileService::Initialize(const Path& sourcePath)`
This function above does the project or game definition for you in runtime. After that, you can use virtual paths 
however you want to use. Since our service will recognize your project folders automatically by using 
`VirtualFileSystem::Mount(const Path& mountPoint, Ref<IVirtualFileSystem> fileSystem)`, you won't have any problem 
on manipulating your files.

### ` void VirtualFileService::Mount(const Path& mountPoint, Ref<IVirtualFileSystem> fileSystem)`
This function above is to mount the folders of the project and game. E.g you created a project by using the launcher. 
The launcher will automatically create the `Assets`, `Cached`, `Scripts`, `Intermediate` folders for you inside of 
your project folder. Then, Flax engine will catch those folders and bind itself with those 4 folders.

### `Ref<IFileStream> VirtualFileSystem::Open(const Path& virtPath, FileMode mode)`
This function above opens your file with `std::fstream`. But to make it convenient, flax engine suggests you to use 
`FileStream`. The function checks your mount point in your path, and decides which fileSystem to use. If you don't add 
mount point in your virtual path, then you may crash the application.

#### For project example
```cpp
// Assuming you already called RuntimeService to get the VirtualFileService

void Something()
{
	auto file = vfsm->Open("/Assets/SomePath/SomeAnotherPath/SomeMorePath/SomeFile.someextension", FileMode::Read);
}
```

#### For game example
```cpp
That is not your concern
```

