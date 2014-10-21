#!/bin/bash

[[ -z $COMPILER ]] && COMPILER="gcc"
DIMENSION=10000
if [[ $COMPILER="gcc" ]]; then
   ./simple_dsymv $DIMENSION
fi
