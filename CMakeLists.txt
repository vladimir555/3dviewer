cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets 3DCore 3DRender 3DInput 3DExtras REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/source)

file(GLOB_RECURSE SOURCE
    ${CMAKE_SOURCE_DIR}/source/*.h
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)

source_group(TREE ${CMAKE_SOURCE_DIR}/source FILES ${SOURCE})

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::3DCore Qt6::3DRender Qt6::3DInput Qt6::3DExtras)
