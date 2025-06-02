cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(sdl2-shooter VERSION 0.1.0 LANGUAGES C CXX)
message(STATUS "项目名称: ${PROJECT_NAME}")

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译类型
if (MSVC)
    # windows
    add_compile_options(/W4)
    # 添加编译选项, 设置 输入代码的编码格式为 utf-8
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
    # linux
    add_compile_options(-Wall -Wextra -Werror -Wpedantic)
endif()


# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
message(STATUS "DEBUG 输出目录: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message(STATUS "RELEASE 输出目录: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")


set(SDL_CUSTOM_PATH "${CMAKE_SOURCE_DIR}/3rd/SDL2/cmake")
message(STATUS "SDL2路径: ${SDL_CUSTOM_PATH}")

set(CMAKE_PREFIX_PATH ${SDL_CUSTOM_PATH})
# #
# ## 查找并载入Cmake预设
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
# #

## 增加判断是否找到SDL库，找到则输出库路径，否则输出错误信息
if(SDL2_FOUND)
    message(STATUS "SDL2 found")
    message(STATUS "SDL Header: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL Library: ${SDL2_LIBRARIES}")
else()
    message(FATAL_ERROR "SDL2 not found")
endif()

add_subdirectory(shooter)