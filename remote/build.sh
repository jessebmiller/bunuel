#!/usr/bin/env bash

set -e

CFLAGS="-Wall -Wextra -O0 -g -lbunuel"
CFILES="main.c"

gcc $CFILES $CFLAGS -o remote

echo "voila."
