export CC=/usr/bin/gcc-8
export CXX=/usr/bin/g++-8

if [ "$1" == "" ]; then
  type="Release"
else
  type="$1"
fi

mkdir -p "./build/linux/$type"
cd "./build/linux/$type"
cmake -DCMAKE_BUILD_TYPE=$type ../../..
cmake --build .
