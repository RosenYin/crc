# Set the minimum version of CMake that can be used，指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.0)
# 定义一个变量用来切换动态库还是可执行文件，0是可执行文件，1是动态库so
set(CUSTOM_COMPILE_OPTIONS "1")
#project name，定义工程名称，并可指定工程支持的语言
set(Target crc)

project(${Target})
# 添加编译参数
add_compile_options(-Wall -std=c99 -O2)
# 定义源文件列表
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/crc.c)

if(CUSTOM_COMPILE_OPTIONS MATCHES "0")
    list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
endif()

#head file pat，向工程添加多个特定的头文件搜索路径 --->相当于指定g++编译器的-I参数
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include )

# 设定编译类型为debug，调试时需要选择debug
set(CMAKE_BUILD_TYPE Debug)

# 将源文件分组以提高IDE项目的可读性
source_group(source FILES ${SOURCE_FILES})
# 创建可执行文件
if(CUSTOM_COMPILE_OPTIONS MATCHES "0")
	add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    )
elseif(CUSTOM_COMPILE_OPTIONS MATCHES "1")
	add_library(${PROJECT_NAME} SHARED 
    ${SOURCE_FILES}
    )
    # 复制头文件到编译路径
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/crc.h ${CMAKE_CURRENT_BINARY_DIR}/crc.h COPYONLY)
endif()

# 将头文件目录添加到可执行文件的包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#add link library
# target_link_libraries(${FS_BUILD_BINARY_PREFIX}sqrt ${LIBRARIES})