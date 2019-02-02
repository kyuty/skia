https://skia.org/user/download


How to download Skia
Install depot_tools and Git
Follow the instructions on Installing Chromium’s depot_tools to download depot_tools (which includes gclient, git-cl, and Ninja). Below is a summary of the necessary steps.

```
git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"
```
depot_tools will also install Git on your system, if it wasn’t installed already.

Clone the Skia repository
Skia can either be cloned using git or the fetch tool that is installed with depot_tools.

```
git clone https://skia.googlesource.com/skia.git
# or
# fetch skia
cd skia
python tools/git-sync-deps
```


https://skia.org/user/build

Quickstart
Run GN to generate your build files.
```
bin/gn gen out/Static --args='is_official_build=true'
bin/gn gen out/Shared --args='is_official_build=true is_component_build=true'
```
If you find you don’t have bin/gn, make sure you’ve run

```
python tools/git-sync-deps
```
GN allows fine-grained settings for developers and special situations.

```
bin/gn gen out/Debug
bin/gn gen out/Release  --args='is_debug=false'
bin/gn gen out/Clang    --args='cc="clang" cxx="clang++"'
bin/gn gen out/Cached   --args='cc_wrapper="ccache"'
bin/gn gen out/RTTI     --args='extra_cflags_cc=["-frtti"]'
```
To see all the arguments available, you can run

```
bin/gn args out/Debug --list
```
Having generated your build files, run Ninja to compile and link Skia.

```
ninja -C out/Static
ninja -C out/Shared
ninja -C out/Debug
ninja -C out/Release
ninja -C out/Clang
ninja -C out/Cached
ninja -C out/RTTI
```

If some header files are missing, install the corresponding dependencies

```
tools/install_dependencies.sh
```

CMake
We have added a GN-to-CMake translator mainly for use with IDEs that like CMake project descriptions. This is not meant for any purpose beyond development.

```
bin/gn gen out/config --ide=json --json-ide-script=../../gn/gn_to_cmake.py
```

error:
```
Scanning dependencies of target HelloWorld
[ 79%] Building CXX object CMakeFiles/HelloWorld.dir/Users/wangdong/github/skia/example/HelloWorld.cpp.o
[ 79%] Linking CXX executable HelloWorld
Undefined symbols for architecture x86_64:
  "sk_app::Window::CreateNativeWindow(void*)", referenced from:
      HelloWorld::HelloWorld(int, char**, void*) in HelloWorld.cpp.o
  "_main", referenced from:
     implicit entry/start for main executable
     (maybe you meant: _jinit_c_main_controller, _jinit_d_main_controller , __ZN8dng_exif15Parse_ifd0_mainER10dng_streamR10dng_sharedjjjjy )
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [HelloWorld] Error 1
make[1]: *** [CMakeFiles/HelloWorld.dir/all] Error 2
make: *** [all] Error 2
```