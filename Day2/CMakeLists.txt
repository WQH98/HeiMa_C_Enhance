cmake_minimum_required(VERSION 3.25)
project(Day2 C)

set(CMAKE_C_STANDARD 11)

# add_executable(Day2 main.c work.c)

file (GLOB_RECURSE files *.c)

#将所有的cpp文件单独生成可执行文件
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()

