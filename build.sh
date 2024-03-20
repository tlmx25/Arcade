if [ "$1" = "--help" ] ||  [ "$1" = "-h" ]; then
  echo "Usage: ./build.sh [re|debug|ninja]"
  echo "re: remove build directory and rebuild"
  echo "debug: build in debug mode"
  echo "ninja: build using ninja"
  exit 0
fi

if [ "$1" = "re"  ]; then
  rm -rf build
  rm -rf cmake-build-debug
fi

if [ "$1" = "debug" ]; then
  echo "Debug mode"
  rm -rf build
  rm -rf cmake-build-debug
  mkdir -p build && cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cmake --build . && cd ..
  exit 0
fi

if [ "$1" = "ninja" ]; then
  echo "Ninja mode"
  rm -rf build
  rm -rf cmake-build-debug
  mkdir -p build && cd build && cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
  exit 0
fi

mkdir -p build && cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && cmake --build . && cd ..
