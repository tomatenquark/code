# Build instructions

Clone the repository and use `cd code`.

## Linux

Tested on: Ubuntu and Debian

```shell
sudo apt-get update
sudo apt-get install -y libsdl-dev libsdl2-mixer-dev libsdl2-image-dev zlib1g-dev libcurl4-openssl-dev
cd ./src
make
```

## Windows

If needed, install [Visual Studio](https://visualstudio.microsoft.com/vs/).
Download, install and setup [MSBuild](https://docs.microsoft.com/en-us/visualstudio/msbuild/msbuild?view=vs-2019).

```bat
cd ./src/vcpp
msbuild /p:PlatformToolset=v142 /property:Platform=x64 tomatenquark.sln
```

## MacOS

```shell
cd ./src/xcode
xcodebuild
```
