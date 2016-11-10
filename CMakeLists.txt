cmake_minimum_required (VERSION 2.6)
project (HashTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

include_directories(${HashTable_SOURCE_DIR})
include_directories(${HashTable_SOURCE_DIR}/include)

file(GLOB HashTable_SRC
    "*.h"
    "*.cpp"
)

add_executable(HashTable ${HashTable_SRC})

TARGET_LINK_LIBRARIES(HashTable  PUBLIC pthread )

