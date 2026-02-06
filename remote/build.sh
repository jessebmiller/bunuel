#!/usr/bin/env bash

set -e

CFLAGS="-Wall -Wextra -O0 -g -lbunuel"
SDL3PATH="../platform/vendor/SDL3-3.4.0/dist"
CFLAGS="$CFLAGS -I$SDL3PATH/include"
CFLAGS="$CFLAGS -L$SDL3PATH/lib64"
CFLAGS="$CFLAGS -lSDL3"
CFILES="main.c"

gcc $CFILES $CFLAGS -o remote

echo "voila."
