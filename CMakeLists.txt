cmake_minimum_required(VERSION 3.20)

project(IAEngine)
enable_testing()

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(IAEngine_IS_TOP_LEVEL ON)
else()
    set(IAEngine_IS_TOP_LEVEL OFF)
endif()

set(IAEngine_ROOT "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

if(TARGET libauxid)
    message(STATUS "IAEngine: Using external LibAuxid provided by parent project")
else()
    message(STATUS "IAEngine: Building standalone, using local LibAuxid submodule")
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libauxid/CMakeLists.txt")
        message(FATAL_ERROR "LibAuxid submodule missing! Run: git submodule update --init --recursive")
    endif()
    add_subdirectory(libauxid)
endif()

auxid_setup_project()

option(IAEngine_BUILD_TESTS "Build unit tests" ${IAEngine_IS_TOP_LEVEL})
option(IAEngine_BUILD_SANDBOX "Build sandbox" ${IAEngine_IS_TOP_LEVEL})

include(cmake/find_deps.cmake)

add_subdirectory(src)

if(IAEngine_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(IAEngine_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()
