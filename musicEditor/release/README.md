# Final Ready-to-Compile Release Instructions
This folder contains the source files / directory tree used to compile the final release of the program. The "musicEditor.pro" file is used to generate makefiles for the project using qmake. Below are compilation instructions.

## Easy Way:
- Install Qt for your system
- Run Qt Creator and navigate to this folder in the source tree
- From the file menu, open the "musicEditor.pro" file and use the default options to open as as project
- Build and run from Qt Creator

## Hard Way:
- On Windows: Download, install, and update MSYS2 - http://www.msys2.org/
- Install the mingw toolchain for your host system as well as qt5:
  - For mingw, example install looks like this: "pacman -S mingw-w64-x86_64-toolchain" (Just hit enter to install all components)
  - For qt5, the command looks like this: "pacman -S mingw-w64-x86_64-qt5"
- Open the "MSYS MinGW x64" (or if your stuck in 2005, x86) and cd to this directory
- Run qmake
- Run mingw32-make
- Output binary should be in the debug folder