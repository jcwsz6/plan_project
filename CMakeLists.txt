cmake_minimum_required(VERSION 3.10) #设置cmake版本

project(plan_project) #获取工程名称 ${PROJECT_NAME}

message("Project name: ${PROJECT_NAME}") #打印工程名称

set(CMAKE_CXX_STANDARD 17) #设置c++版本，这里设置为c++17
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_BUILD_TYPE Debug) #设置构建调试模式
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O2")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 指定可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加头文件路径
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("E:/codeconfig/TDM/x86_64-w64-mingw32/include")
link_libraries("E:/codeconfig/TDM/x86_64-w64-mingw32/lib")

# 查找所有 .cpp 文件
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} easyx)


