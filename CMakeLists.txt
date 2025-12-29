cmake_minimum_required(VERSION 3.16)

project(Material3Generator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui)
find_package(absl REQUIRED)

include(FetchContent)

message(STATUS "Fetching Google material-color-utilities...")
FetchContent_Declare(
    material_color_utilities
    GIT_REPOSITORY https://github.com/material-foundation/material-color-utilities.git
    GIT_TAG        main # 158b9c185a25c53fddd051cba811d542e6b94d68
    GIT_SHALLOW    TRUE # FALSE
)

FetchContent_GetProperties(material_color_utilities)
if(NOT material_color_utilities_POPULATED)
    FetchContent_Populate(material_color_utilities)
endif()

set(MCU_SRC_DIR "${material_color_utilities_SOURCE_DIR}/cpp")

# 包含头文件路径，这样代码里就能写 #include "scheme/scheme_tonal_spot.h"
include_directories(${MCU_SRC_DIR})

# 递归查找所有 .cc 文件
file(GLOB_RECURSE MCU_SOURCES "${MCU_SRC_DIR}/*.cc")

# 排除掉测试文件 (_test.cc) 以免编译报错
list(FILTER MCU_SOURCES EXCLUDE REGEX ".*_test\\.cc$")

message(STATUS "Google Material Sources: ${MCU_SOURCES}")

qt_add_executable(appMaterial3Generator
    main.cpp
    MaterialColorGenerator.h
    MaterialColorGenerator.cpp
    ${MCU_SOURCES} # 把 Google 的源码编译进来
)

target_include_directories(appMaterial3Generator PRIVATE 
    # 1. 添加源码根目录 (解决 Google 内部的 #include "cpp/..." )
    ${material_color_utilities_SOURCE_DIR}
    ${MCU_SRC_DIR}
)

# 链接 Qt 库
target_link_libraries(appMaterial3Generator PRIVATE 
    Qt6::Quick 
    Qt6::Gui
    absl::strings
    absl::flat_hash_map
    absl::base 
    absl::log_internal_message # 解决 RawLog 报错
    absl::check                # 部分版本需要这个
)

# 添加 QML 模块
qt_add_qml_module(appMaterial3Generator
    URI "M3Tools"
    VERSION 1.0
    QML_FILES Main.qml
)