# Éditeur de cartes pour Dungeon Keeper 2

(Only available in french)

Ce programme permet de lire, modifier et créer des cartes pour le jeu Dungeon Keeper 2.

Requirements:
- CMake
- Visual Studio 2022

How to build:
- `cmd` - if you are in powershell
- `mkdir build && cd build`
- `"D:\Program Files\Visual Studio Community\2022\VC\Auxiliary\Build\vcvars32.bat"`
- `cmake -DCMAKE_BUILD_TYPE=Debug -GNinja ..`
- `cmake --build .`
- `"..\Binaries\Editor.exe"`
