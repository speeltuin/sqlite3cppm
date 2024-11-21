# SPDX-License-Identifier: MIT
# Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

cmake_minimum_required(VERSION 3.29...3.31)

project(
    SQLite3cppm
    VERSION 0.1.0
    DESCRIPTION "SQLite C++ Module"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(CodeCoverage)
    include(CTest)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    option(BUILD_SHARED_LIBS "Build using shared libraries." ON)
endif()

include(FetchContent)
include(GenerateExportHeader)
include(GNUInstallDirs)

option(SQLITE_BUILD_SHELL "" OFF)
add_subdirectory(extern/sqlite-amalgamation-cmake-buildsystem)

add_library(sqlite3cppm)
add_library(SQLite3cppm::sqlite3cppm ALIAS sqlite3cppm)

set_target_properties(
    sqlite3cppm
    PROPERTIES
        VERSION ${SQLite3cppm_VERSION}
        SOVERSION ${SQLite3cppm_VERSION_MAJOR}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

generate_export_header(sqlite3cppm)

target_sources(
    sqlite3cppm
    PUBLIC FILE_SET HEADERS
        BASE_DIRS
            "${CMAKE_CURRENT_BINARY_DIR}"
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm_export.h"
    PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/include/sqlite3cppm.cppm"
)

target_include_directories(
    sqlite3cppm
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    PUBLIC "$<INSTALL_INTERFACE:include>"
)

target_compile_features(
    sqlite3cppm
    PUBLIC cxx_std_20
)

target_link_libraries(
    sqlite3cppm
    PUBLIC SQLite::SQLite3
)

if(BUILD_TESTING)
    option(BUILD_GMOCK "" OFF)
    option(INSTALL_GTEST "" OFF)
    add_subdirectory(extern/googletest)
    include(GoogleTest)

    add_subdirectory(tests)
endif()

install(
    TARGETS
        sqlite3cppm
    EXPORT SQLite3cppmTargets
    FILE_SET HEADERS
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET CXX_MODULES
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLite3cppm/src"
)

install(
    EXPORT SQLite3cppmTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLite3cppm"
    NAMESPACE SQLite3cppm::
    FILE sqlite3cppm-targets.cmake
    CXX_MODULES_DIRECTORY .
)

export(
    EXPORT SQLite3cppmTargets
    NAMESPACE SQLite3cppm::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm-targets.cmake"
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLite3cppm"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/sqlite3cppm-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLite3cppm"
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(InstallRequiredSystemLibraries)
    set(CPACK_PACKAGE_VERSION_MAJOR "${SQLite3cppm_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${SQLite3cppm_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${SQLite3cppm_VERSION_PATCH}")
    include(CPack)
endif()
