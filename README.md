# clang_demo

方法一
使用gcc
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
# cmake .. && make

使用clang
export CC=/usr/bin/clang++
export CXX=/usr/bin/clang++
# cmake .. && make

方法二
在CMakeLists.txt中类似如下的修改即可

注意，一定要写在project指令之前，否则无效。

SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)

方法三
当前的这种办法:写一个cmake,添加各种参数,在cmake的时候执行
