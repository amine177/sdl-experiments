cmake_minimum_required(VERSION 2.6)
project(firstStep)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${firstStep_SOURCE_DIR}/cmake")
set(BIN_DIR ${firstStep_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (MSVC)
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

add_subdirectory(Lesson1)

if (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${PROJECT_SOURCE_DIR}/res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

