cmake_minimum_required(VERSION 3.10)
project(SPI_driver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES src/CPPSPI/cppspi.cpp)



idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS include)

add_executable(SPI_driver src/main.cpp ${SOURCES})
