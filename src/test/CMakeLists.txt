cmake_minimum_required(VERSION 3.1)
project(controller_test CXX)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory) and run CMake from there.
    You may need to remove CMakeCache.txt." )
endif()


enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(SRC_ROOT_DIR "../")
set(SRC_INCLUDE_DIR ${SRC_ROOT_DIR}/include)
set(APP_MAIN_DIR ${SRC_ROOT_DIR}/main)
set(LIB_GTESTS gtest gtest_main)

# Library
add_library(renderer STATIC ${APP_MAIN_DIR}/renderer.cpp)
target_include_directories(renderer PRIVATE ${SRC_INCLUDE_DIR})
target_link_libraries(renderer PUBLIC stdc++ )

add_library(controller STATIC ${APP_MAIN_DIR}/controller.cpp)
target_include_directories(controller PRIVATE ${SRC_INCLUDE_DIR} /usr/include/httpd /usr/include/apr-1/)
target_link_libraries(controller PUBLIC stdc++ renderer)

#testing execution file

add_executable(request_test request_test.cpp)
target_include_directories(request_test PRIVATE ${SRC_INCLUDE_DIR} )
target_link_libraries(request_test PRIVATE ${LIB_GTESTS})
add_test(NAME request_test COMMAND $<TARGET_FILE:request_test>)

add_executable(renderer_test renderer_test.cpp)
target_include_directories(renderer_test PRIVATE ${SRC_INCLUDE_DIR} )
target_link_libraries(renderer_test PRIVATE ${LIB_GTESTS} renderer)
add_test(NAME renderer_test COMMAND $<TARGET_FILE:renderer_test>)

add_executable(controller_test controller_test.cpp)
target_include_directories(controller_test PRIVATE ${SRC_INCLUDE_DIR} )
target_link_libraries(controller_test PRIVATE ${LIB_GTESTS} controller)
add_test(NAME controller_test COMMAND $<TARGET_FILE:controller_test>)