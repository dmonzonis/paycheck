#!/bin/bash

# Script to execute the program. This script is to be placed on the same folder as the compiled binary.
# It's only a temporary solution for working with shared libraries, until a static binary is released.

BASEDIR=$(dirname "$0")
export LD_LIBRARY_PATH=$BASEDIR
$BASEDIR/paycheck
