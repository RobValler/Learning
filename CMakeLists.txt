cmake_minimum_required(VERSION 3.5.0)
project ( Learning )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set (CMAKE_CXX_STANDARD 14)
set (Wall)
set (W1)
set (Wfloat-conversion)


#PACKAGES
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

#INCLUDES
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../DevFramework/Logger)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src})

#SOURCE FILES
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/test/*.cpp
)

file(GLOB HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.h
)

#GENERATE
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} )
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${GTEST_LIBRARIES})

