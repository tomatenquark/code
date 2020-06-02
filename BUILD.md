# Build instructions

`Tomatenquark` relies on the excellent `vcpkg` package management. In order to get started you will need the following *ingredients*.

- `git`
- `cmake`


## Platform specific dependencies for building

### Windows

You will need a recent version of [Visual Studio](https://visualstudio.microsoft.com/de/) alongside the C/C++ extension pack.

### Ubuntu

In order for compilation to work you must have a version of `libgl` available. We recommend `libgl1-mesa-dev`. Go get it using `sudo apt-get install libgl1-mesa-dev`.

### OSX

On OSX we recommend using `XCode`. However, `tomatenquark` **may**  be built using plain `Makefile`.


## Building the code

In order to build the project follow these steps:

1. clone `vcpkg` into a location of your choosing and [set it up](https://github.com/microsoft/vcpkg#quick-start).
2. clone `code` into a location of your choosing
3. installing the necessary dependencies
4. platform-dependant compilation

### Installing necessary dependencies

Navigate to your `vcpkg` directory and install a triplet of your choosing:

```
./vcpkg install @/path/to/code/cmake/triplets/linux64
#.\vcpkg install @/path/to/code/cmake/triplets/windows64 # on windows
```

### Platform-dependant compilation

#### Windows

```
cd \path\to\code
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
msbuild /property:Platform=x64 /t:tomatenquark tomatenquark.sln
```

#### OSX

```
cd /path/to/code
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
xcodebuild -arch x86_64 build
```

If you prefer Makefiles over project files, head straight to the linux section.

### Linux

```
cd /path/to/code
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
make tomatenquark
```

## Reduced version for server-only

The server only version works with fewer dependencies. You will need only to install `enet` and `zlib`.
When building the code select the `tomaten_server` or `tomaten_master` target, e.g:

```
.\vcpkg install enet zlib --triplet x64-linux
# (cd to code)
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
make tomaten_server
```
