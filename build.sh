#!/usr/bin/env bash

set -e

CFLAGS="-Wall -Wextra -O0 -g -lbunuel"
SDL3PATH="platform/vendor/SDL3-3.4.0/dist"
CFLAGS="$CFLAGS -I$SDL3PATH/include"
CFLAGS="$CFLAGS -L$SDL3PATH/lib64"
CFLAGS="$CFLAGS -lSDL3"
BUNUEL_CFILES="platform/lib.c allocate/lib.c string/lib.c log/lib.c"

mkdir -p _build

echo "Building Bunuel lib v0 test"
gcc $CFLAGS -o _build/test_lib_v0 test_lib_v0.c $BUNUEL_CFILES
echo "Running test"
./_build/test_lib_v0
echo

echo "Building Bunuel lib v1 test"
echo "" > test_lib_v1.h # clear the file
source test_lib_v1_codegen.sh >> test_lib_v1.h
gcc $CFLAGS -o _build/test_lib_v1 test_lib_v1.c $BUNUEL_CFILES
echo "Running test"
./_build/test_lib_v1
echo

echo "Building library artifacts"
for src in $BUNUEL_CFILES; do
	gcc $CFLAGS -c $src -o "_build/${src%/lib.c}.o"
done
ar rcs _build/libbunuel.a _build/*.o

echo "Building namer"
(
	cd namer || exit
	./build.sh
	./namer
)

echo "Building /remote/"
(
	cd remote || exit
	./build.sh
	#./test_remote
)

echo "voila."
