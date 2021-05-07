# How to get started
First off this project uses CMake's build system. Depending on the OS you have it installed. Also you'll need a compiler. Either GCC's G++ compiler. Clang or Microsoft's Visual C++ compiler. Others aren't guaranteed to work.

# Binary Downloads
https://cmake.org/download/#latest


## Linux OSes
Depends on the Distro that you have.

### Debian/ubuntu
` apt-get install cmake g++ `


### Arch
` pacman -Syu cmake g++`

## Windows
After downloading and installing the Cmake binary you'll also have to have a compiler. You can use cygwin's G++, or microsoft's visual C++ compiler.

### MSVC
https://visualstudio.microsoft.com/downloads#other
### Cygwin
https://cygwin.com/install.html

## Mac OSX
You're on your own here. I don't have a mac.


# Getting ready to use the code.
Either download the source code from the release page or or clone the repo. After navigating to the folder open up a command prompt and run the following commands. This assumes that you're _not_ already using CLion, Visual Studio Code, Visual Studio, or another IDE and have created this code as a project within it. This is solely for standalone builds.

## Making a build directory
It's best that you have a directory for the debug and also the release builds.
`mkdir release`

