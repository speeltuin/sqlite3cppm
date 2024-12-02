# SPDX-License-Identifier: MIT
# Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(
    sqlite3cppm_test
)

target_sources(
    sqlite3cppm_test
    PRIVATE
        sqlite3cppm_test.cpp
)

target_link_libraries(
    sqlite3cppm_test
    PRIVATE
        SQLite3cppm::sqlite3cppm
        GTest::gtest_main
)

gtest_discover_tests(sqlite3cppm_test)
