# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (project)
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/build)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)       #设置可执行文件的输出目录

link_directories(${PROJECT_SOURCE_DIR}/build/lib)
#set (CMAKE_INCLUDE_CURRENT_DIR ON)

# 检查系统是否支持 pow 函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (pow HAVE_POW)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
 )

# 是否使用自己的 MathFunctions 库  ON  OFF
option (USE_MYMATH
       "Use provided math implementation" ON)



set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 添加 子目录
add_subdirectory(src/Log)
add_subdirectory(src/Common)
add_subdirectory(src/WindowManager)
add_subdirectory(src/ModuleManager)
add_subdirectory(src/SurfaceManager)
add_subdirectory(src/PropertyClient)
add_subdirectory(src/SurfaceManagerClient)


set(Use_MyMath 0)
# 是否加入 MathFuntion 库
if (USE_MYMATH)
   set(Use_MyMath 1)
endif (USE_MYMATH)


# 是否加入 MathFuntion 库
if (NOT HAVE_POW)
   set(Use_MyMath 1)
endif (NOT HAVE_POW)

if (Use_MyMath)
   add_subdirectory(src/Math)
endif (Use_MyMath)

add_subdirectory(examples)


# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)

#生成二进制安装包：cpack -C CPackConfig.cmake
#生成源码安装包 cpack -C CPackSourceConfig.cmake
