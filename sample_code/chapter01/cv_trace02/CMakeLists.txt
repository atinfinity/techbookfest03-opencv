cmake_minimum_required(VERSION 2.8)
project(cv_trace02)

find_package(OpenCV REQUIRED)
file(GLOB SOURCES "*.cpp" "*.c" "*.h" "*.hpp")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native")
endif()

if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	add_executable(cv_trace02 ${SOURCES})
	target_link_libraries(cv_trace02 ${OpenCV_LIBS})
endif(OpenCV_FOUND)
