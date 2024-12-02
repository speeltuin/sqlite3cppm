// SPDX-License-Identifier: MIT
// Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

#define sqlite3 sqlite3_db
#include <sqlite3.h>
#undef sqlite3

#include "gtest/gtest.h"

import sqlite3cppm;

TEST(SQLite3cppmTest, LibVersion)
{
    EXPECT_STREQ(sqlite3::libversion(), SQLITE_VERSION);
    EXPECT_STREQ(sqlite3::libversion(), sqlite3::version);
    EXPECT_STREQ(sqlite3::libversion(), sqlite3::VERSION);
    EXPECT_STREQ(sqlite3::sourceid(), sqlite3::SOURCE_ID);
    EXPECT_EQ(sqlite3::libversion_number(), sqlite3::VERSION_NUMBER);
}

TEST(SQLite3cppmTest, WindowsDirectories)
{
    char temp_dir[] = "C:\\TEMP";
    char data_dir[] = "C:\\DATA";
    ::sqlite3_temp_directory = temp_dir;
    ::sqlite3_data_directory = data_dir;
    EXPECT_EQ(sqlite3::temp_directory, temp_dir);
    EXPECT_EQ(sqlite3::data_directory, data_dir);
}

#if !defined(SQLITE_OMIT_COMPILEOPTION_DIAGS)
TEST(SQLite3cppmTest, CompileOptions)
{
    EXPECT_NE(sqlite3::compileoption_used("THREADSAFE"), 0);
    EXPECT_NE(sqlite3::compileoption_get(0), nullptr);
}
#endif

TEST(SQLite3cppmTest, ThreadSafe)
{
    /** @todo Replace 2 with SQLITE_THREADSAFE **/
    EXPECT_EQ(sqlite3::threadsafe(), 2);
}
