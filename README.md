# Barrage
A C++ game engine for building bullet hell games.

# Getting the engine
## Windows
Required:
- Git for Windows
- Visual Studio 2019 or above

Steps:
1. Open Visual Studio Installer and verify that the "Desktop development with C++" workload is installed.
2. Clone the repository and initialize submodules with the following git commands:
```
git clone https://github.com/Dragonscale-Games/Barrage.git
cd Barrage
git submodule init
git submodule update
```
3. Open the root folder of the project in Visual Studio.
4. Wait for CMake generation to finish.
5. Select "Release" as the build configuration and "Game.exe" or "Editor.exe" as the startup item.
6. Press F5 to build and run the executable.
