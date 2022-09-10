rmdir /s /q build
cmake -Bbuild -G "MinGW Makefiles" -DGLFW_BUILD_DOCS=OFF

cd build
make -j 8
start minecraft-clone.exe