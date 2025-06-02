cmake_minimum_required(VERSION 3.10)

project(shooter VERSION 0.1.0 LANGUAGES C CXX)
message(STATUS "项目名称: ${PROJECT_NAME}")

# 设置输出
set(TARGET_NAME ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")

# 添加可执行文件
add_executable(${TARGET_NAME} ${SOURCES} )

# 链接库
target_link_libraries(${TARGET_NAME} 
                        ${SDL2_LIBRARIES}
                        SDL2_image::SDL2_image
                        SDL2_mixer::SDL2_mixer
                        SDL2_ttf::SDL2_ttf
)

target_include_directories(${TARGET_NAME} PRIVATE include)

if(MSVC)
    target_link_options(${TARGET_NAME} PRIVATE "/SUBSYSTEM:windows")
endif()