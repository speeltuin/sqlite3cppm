# SPDX-License-Identifier: MIT
# Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

add_executable(
    sqlite3cppm_test
)

set_target_properties(
    sqlite3cppm_test
    PROPERTIES
        INSTALL_RPATH "$ORIGIN/../lib"
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
