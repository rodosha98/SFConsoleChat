cmake_minimum_required(VERSION 3.0.0)
project(ConsoleChat VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${ConsoleChat_SOURCE_DIR}/include)
add_executable(Chat src/User.cpp src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
