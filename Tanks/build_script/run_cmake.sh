#!/bin/bash

# Скрипт проверки сборки вне VSCode и прочих редакторов

#PREFIX_PATH="/opt/Qt6.4.3/6.4.3/gcc_64;/opt/Qt5.12.3/5.12.3/gcc_64"

start=$(date +%s)

cd ../
mkdir ./build
cd ./build
cmake ../ -DCMAKE_BUILD_TYPE=Release  \
-DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake
make -j1

end=$(date +%s)

echo Build time was  $(($end-$start)) seconds.

