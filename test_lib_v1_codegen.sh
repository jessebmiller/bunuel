#!/usr/bin/env bash

set -e

CAP=3

source codegen.sh

gen_fixed_set_v0 int $CAP int_set
gen_fixed_set_v0 float $CAP float_set
