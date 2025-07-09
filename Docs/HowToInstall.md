# Flax Engine Documentation

## How to run Flax Engine from source code

To run the engine, you need a couple of SDKs installed on your system. The engine supports the following SDKs:

- [Vulkan SDK 1.4.313](https://vulkan.lunarg.com/sdk/home)
- [Qt SDK 6.9.0](https://www.qt.io/download-qt-installer)
- [Python 3.12](https://www.python.org/downloads/release/python-3120/)

Since the source code expects you to use CMake v3.26 or higher, I will highly recommend you to install Vistual Studio 
2022 with the following components:
- C++ CMake tools for Windows
- C++ 2022 Redistributable Update
- C++ Build Insights
- MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)
- C++ AddressSanitizer
- C++ profiling tools
- C++ core features
- C++ ATL for latest v143 build tools (x86 & x64)

### Run via Visual Studio 2022
To build the engine, you don't need to use CMake's GUI or command line. You can use the series of commands below in your Powershell terminal.

```powershell
git clone https://github.com/mtuncbilek95/Flax.git
cd Flax
Start-Process "devenv.exe" -ArgumentList "."
```

This command order will Clone, move into Engine's directory and open the project in Visual Studio 2022. If you have the required SDKs and extensions installed,
Visual Studio will automatically detect the CMake files and generate build files for you. After that you can compile the project. 


### Run Engine

The engine has two different executables. One is the Editor and the other is Flaxbox. You can choose Editor and run it to see the editor interface. Flaxbox is
there to test the engine runtime without the editor. You may find it empty or filled with some sample code.
