cmake_minimum_required(VERSION 3.22.0)
project ( Learning )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set (CMAKE_CXX_STANDARD 17)
set (Wall)
set (W1)
set (Wfloat-conversion)

#CONAN PACKAGES
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#INCLUDES
include_directories(${CMAKE_SOURCE_DIR}/src)

#SOURCE FILES
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/test/*.cpp
)

file(GLOB HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/test/*.h
)

#SOURCE FILES
file(GLOB DATA
    ${CMAKE_SOURCE_DIR}/conanfile.txt
    ${CMAKE_SOURCE_DIR}/README.md
)

#GENERATE
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} )
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
