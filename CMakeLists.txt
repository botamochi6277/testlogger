cmake_minimum_required(VERSION 3.3)
project(log_async)

# FIND_PACKAGE( Boost 1.60 COMPONENTS system REQUIRED )
# INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
# message(STATUS "Boost!: " ${Boost_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES log_async.cpp mcp3008Spi.cpp mcp3x08Spi.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lpthread -fpermissive)
