#!/bin/bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2024 AlgorIT Software Consultancy, the Netherlands

declare -r git_root="$(git rev-parse --show-toplevel)"
declare -r cov_dir="${git_root}/out/coverage"
declare -r html_dir="${git_root}/out/html"
declare -r lcovrc="${git_root}/.lcovrc"

# Run coverage workflowConfigure the build tree
cmake --workflow --preset cov

# Collect the code coverage
llvm-profdata merge -sparse $(find "${cov_dir}" -name 'pid-*.profraw') -o "${cov_dir}/test.profdata"
llvm-cov export -format=lcov -instr-profile="${cov_dir}/test.profdata" $(find "${cov_dir}/bin" -type f -perm -100 -exec echo -n \ -object {} \;) > "${cov_dir}/lcov-all.info"

# Filter the code coverage
lcov -r "${cov_dir}/lcov-all.info" '*/_deps/*' -o "${cov_dir}/lcov.info" --config-file "${lcovrc}" > /dev/null

# Generate html report
test -d "${html_dir}" && rm -rf "${html_dir}"
genhtml --output-directory "${html_dir}" "${cov_dir}/lcov.info" --config-file "${lcovrc}"
