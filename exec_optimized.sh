#!/bin/bash

[[ -z $COMPILER ]] && COMPILER="gcc"
DIMENSION=10000
if [[ $COMPILER="gcc" ]]; then
   ./optimized_dsymv $DIMENSION
fi
