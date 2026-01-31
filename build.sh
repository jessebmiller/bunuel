#! /bin/bash

set -e

CFLAGS="-Wall -Wextra -O0 -g"

mkdir -p _build

echo "Building Bunuel lib v0 test"
gcc $CFLAGS -o _build/test_lib_v0 test_lib_v0.c lib.c
echo "Running test"
./_build/test_lib_v0
echo

echo "Building Bunuel lib v1 test"
gcc $CFLAGS -o _build/test_lib_v1 test_lib_v1.c lib.c
echo "Running test"
./_build/test_lib_v1
echo

echo "fin."
