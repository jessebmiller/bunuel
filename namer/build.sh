#! /usr/bin/env bash

set -e

CFLAGS="-Wall -Wextra -O0 -g -lbunuel"

gcc main.c $CFLAGS -o namer
