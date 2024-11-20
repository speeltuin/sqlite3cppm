#!/bin/bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

declare -r git_root="$(git rev-parse --show-toplevel)"
declare -r cov_dir="${git_root}/build/cov"
declare -r cov_make_dir="${cov_dir}/make"
declare -r cov_data_dir="${cov_dir}/data"
declare -r cov_html_dir="${cov_dir}/html"
declare -r lcovrc="${git_root}/scripts/lcovrc"

test -d "${cov_data_dir}" && rm -rf "${cov_data_dir}"
test -d "${cov_html_dir}" && rm -rf "${cov_html_dir}"

declare -x CC=clang
declare -x CXX=clang++
declare -x LLVM_PROFILE_FILE="${cov_data_dir}/pid-%p.profraw"

# Configure the build tree
cmake -S "${git_root}" -B "${cov_make_dir}" -G Ninja -DCMAKE_BUILD_TYPE:STRING=Coverage -DBUILD_SHARED_LIBS:BOOL=OFF

# Build the targets
cmake --build "${cov_make_dir}"

# Run the test suites
cmake --build "${cov_make_dir}" --target test

# Collect the code coverage
llvm-profdata merge -sparse "${cov_data_dir}"/pid-*.profraw -o "${cov_data_dir}/test.profdata"
llvm-cov export -format=lcov -instr-profile="${cov_data_dir}/test.profdata" $(find "${cov_make_dir}/bin" -type f -perm -100 -exec echo -n \ -object {} \;) > "${cov_data_dir}/lcov-all.info"

# Filter the code coverage
lcov -r "${cov_data_dir}/lcov-all.info" '*/extern/*' '*/tests/*' -o "${cov_data_dir}/lcov.info" --config-file "${lcovrc}"

# Generate html report
genhtml --output-directory "${cov_html_dir}" "${cov_data_dir}/lcov.info" --config-file "${lcovrc}"
