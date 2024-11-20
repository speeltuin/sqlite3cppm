// SPDX-License-Identifier: MIT
// Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

#include "gtest/gtest.h"
#include <cstring>

import sqlite3cppm;

TEST(SQLitecppmTest, LibVersion)
{
    EXPECT_STREQ(sqlite3::libversion(), sqlite3::version);
    EXPECT_STREQ(sqlite3::libversion(), sqlite3::VERSION);
    EXPECT_EQ(sqlite3::libversion_number(), sqlite3::VERSION_NUMBER);
    EXPECT_STREQ(sqlite3::sourceid(), sqlite3::SOURCE_ID);
}
