# /usr/bin/env bash

set -e

NAME="test_platform"
CFLAGS="-Wall -Wextra -O0 -g -lbunuel"
CFILES="$NAME.c"

gcc $CFILES $CFLAGS -o $NAME

echo "voila."
