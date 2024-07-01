
# CMAKE的最低版本
cmake_minimum_required(VERSION 3.22.1)

# 项目名称
project("liantian")

# 添加动态库，指定库名称、类型、相对路径
add_library(
        ${CMAKE_PROJECT_NAME} SHARED
        main.cpp SignUtil.cpp Util.cpp
        my_sha.cpp my_aes.cpp my_base64.cpp)


# 指定头文件路径
include_directories(${ANDROID_ABI}/include/)

# 链接库
target_link_libraries(${CMAKE_PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_ABI}/lib/libcrypto.a
        ${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_ABI}/lib/libssl.a
        android
        log)