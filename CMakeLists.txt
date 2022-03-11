cmake_minimum_required(VERSION 3.10)

project(chat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt setup
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

#if(NOT DEFINED ENV{QT6_DIR})
#	message(FATAL_ERROR "QT6_DIR was not found")
#endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}$ENV{QT6_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_compile_options(-std:c++17 -D_ITERATOR_DEBUG_LEVEL=0 -MT -MD)

add_executable(${PROJECT_NAME}
	SourceFiles/main.cpp
	SourceFiles/SocketManager.h
	SourceFiles/SocketManager.cpp
	SourceFiles/Server.h
	SourceFiles/Server.cpp
)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
