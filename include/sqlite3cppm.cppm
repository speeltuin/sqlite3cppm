// SPDX-License-Identifier: MIT
// Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

module;

#define sqlite3 sqlite3_db
#include <sqlite3.h>
#undef sqlite3

#include "sqlite3cppm_export.h"
#include <iostream>

export module sqlite3cppm;

export namespace  sqlite3
{

SQLITE3CPPM_EXPORT constexpr const char VERSION[] = SQLITE_VERSION;
SQLITE3CPPM_EXPORT constexpr const int VERSION_NUMBER = SQLITE_VERSION_NUMBER;
SQLITE3CPPM_EXPORT constexpr const char SOURCE_ID[] = SQLITE_SOURCE_ID;

using db = sqlite3_db;
using stmt = sqlite3_stmt;

SQLITE3CPPM_EXPORT const char (&version)[] = ::sqlite3_version;
SQLITE3CPPM_EXPORT char *&temp_directory = ::sqlite3_temp_directory;
SQLITE3CPPM_EXPORT char *&data_directory = ::sqlite3_data_directory;

[[nodiscard]]
SQLITE3CPPM_EXPORT const char* libversion() noexcept
{
    return ::sqlite3_libversion();
}

[[nodiscard]]
SQLITE3CPPM_EXPORT int libversion_number() noexcept
{
    return ::sqlite3_libversion_number();
}

[[nodiscard]]
SQLITE3CPPM_EXPORT const char* sourceid() noexcept
{
    return ::sqlite3_sourceid();
}

} // namespace sqlite3
