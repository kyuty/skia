download:

git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"

git clone https://skia.googlesource.com/skia.git
# or
# fetch skia
cd skia
python2 tools/git-sync-deps
tools/install_dependencies.sh

gn:
bin/gn gen out/Debug
cd out/Debug
ninja -C .

cmake:
bin/gn gen out/config_flutter --ide=json --json-ide-script=../../gn/gn_to_cmake.py
