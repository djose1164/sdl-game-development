cmake_minimum_required(VERSION 3.0.0)
project(AlienAttack VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

find_package(tinyxml2 REQUIRED)
include_directories(${tinyxml2_INCLUDE_DIRS})

add_executable(AlienAttack src/main.cpp)
target_include_directories(AlienAttack PUBLIC
                            "${CMAKE_SOURCE_DIR}/include/"
)
target_link_libraries(AlienAttack ${SDL2_LIBRARIES})
target_link_libraries(AlienAttack ${tinyxml2_LIBRARIES})

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CPack)
