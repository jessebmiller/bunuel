# /usr/bin/env bash

set -e

NAME="test_platform"
CFLAGS="-Wall -Wextra -O0 -g -lbunuel"
SDL3PATH="vendor/SDL3-3.4.0/dist"
CFLAGS="$CFLAGS -I$SDL3PATH/include"
CFLAGS="$CFLAGS -L$SDL3PATH/lib64"
CFLAGS="$CFLAGS -lSDL3"
CFILES="$NAME.c lib.c"

gcc $CFILES $CFLAGS -o $NAME

./test_platform

echo "voila."
