download:

```
git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"

git clone https://skia.googlesource.com/skia.git
# or
# fetch skia
cd skia
python2 tools/git-sync-deps
tools/install_dependencies.sh
```
gen && build:

```
gn:
bin/gn gen out/debug_flutter
cd out/config_flutter
ninja -C .

// 不推荐使用该方式
cmake:
bin/gn gen out/config_flutter --ide=json --json-ide-script=../../gn/gn_to_cmake.py

// 推荐使用 gn 方式编译
脚本编译 hello world
./01_build_hello_world.sh

脚本执行 hello world
./01_hello_world.sh
```

环境搭建
```
下载 vs code, 配置插件 c++ Intellisense, 目的是为了方便快速跳转

C++ Intellisense 插件 需要 global 和 gtags 6.6版本

// 卸载系统原来的 老版本 gtags global
sudo apt-get --purge remove gtags
sudo apt-get --purge remove global

// 下载 & 编译 & 安装 新版本 gtags
sudo apt build-dep global
sudo apt install libncurses5-dev libncursesw5-dev
axel -n 8 https://ftp.gnu.org/pub/gnu/global/global-6.6.tar.gz

./configure
make
sudo make install

// 会 install 在 /user/local/bin 目录

gtags --version 6.6版本

打开 vs code, ctrl + shfit + p, 搜索 setting.js 并打开, 其目录为 ~/.config/Code/User/settings.json 
添加 
"codegnuglobal.executable": "/usr/local/bin/global",
"codegnuglobal.encoding": "utf8"

参考链接: https://blog.csdn.net/Levi_Huang/article/details/86510096
参考链接: https://github.com/austin-----/code-gnu-global

在 skia 根目录下, 执行 gtags -v
```

从 example/HelloWorld.cpp 下手阅读