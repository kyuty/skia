Quickstart
Run GN to generate your build files.
```
bin/gn gen out/Static --args='is_official_build=true'
bin/gn gen out/Shared --args='is_official_build=true is_component_build=true'
```
If you find you don’t have bin/gn, make sure you’ve run

python tools/git-sync-deps
GN allows fine-grained settings for developers and special situations.

```
bin/gn gen out/Debug
bin/gn gen out/Release  --args='is_debug=false'
bin/gn gen out/Clang    --args='cc="clang" cxx="clang++"'
bin/gn gen out/Cached   --args='cc_wrapper="ccache"'
bin/gn gen out/RTTI     --args='extra_cflags_cc=["-frtti"]'
```
To see all the arguments available, you can run

bin/gn args out/Debug --list
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
