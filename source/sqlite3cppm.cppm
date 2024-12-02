// SPDX-License-Identifier: MIT
// Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

module;

#define sqlite3 sqlite3_db
#include <sqlite3.h>
#undef sqlite3

#include "sqlite3cppm_export.h"

#if defined(_COVERAGE)
#define SQLITE3CPPM_INLINE
#else
#define SQLITE3CPPM_INLINE inline
#endif

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

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
const char* libversion() noexcept
{
    return ::sqlite3_libversion();
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
const char* sourceid() noexcept
{
    return ::sqlite3_sourceid();
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int libversion_number() noexcept
{
    return ::sqlite3_libversion_number();
}

#if !defined(SQLITE_OMIT_COMPILEOPTION_DIAGS)
[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int compileoption_used(const char *zOptName) noexcept
{
    return ::sqlite3_compileoption_used(zOptName);
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
const char *compileoption_get(int N) noexcept
{
    return ::sqlite3_compileoption_get(N);
}
#endif

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int threadsafe() noexcept
{
    return ::sqlite3_threadsafe();
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int close(db* db) noexcept
{
    return ::sqlite3_close(db);
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int close_v2(db* db) noexcept
{
    return ::sqlite3_close_v2(db);
}

[[nodiscard]] SQLITE3CPPM_EXPORT SQLITE3CPPM_INLINE
int exec(db* db, const char* zSql, int (*xCallback)(void*,int,char**,char**), void* pArg, char**pzErrMsg) noexcept
{
    return ::sqlite3_exec(db, zSql, xCallback, pArg, pzErrMsg);
}

} // namespace sqlite3
