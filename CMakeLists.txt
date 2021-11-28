cmake_minimum_required(VERSION 2.8)
project(demo)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
# 编译器和C++标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
include(${CMAKE_SOURCE_DIR}/coroutine.cmake)
# 第三方库
include_directories(${CMAKE_SOURCE_DIR}/third_party/include)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/third_party)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${PROJECT_SOURCE_DIR}/third_party/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath,$ORIGIN/third_party/lib/:$ORIGIN/../third_party/lib/") # 第三方库查找路径
# 业务相关
add_subdirectory(example)
add_executable(main main.cpp)
target_link_libraries(main pthread)