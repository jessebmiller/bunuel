#!/usr/bin/env bash

set -e

NAME="main"
CFLAGS="-Wall -Wextra -fdiagnostics-absolute-paths -O0 -g -lbunuel"
CFILES="$NAME.c"

gcc $CFILES $CFLAGS -o $NAME

echo "voila."
