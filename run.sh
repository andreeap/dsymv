#!/bin/bash
#
# Author: Pirvulescu Andreea Monica
#
# Submit jobs to queues, use different compilers
#


module load libraries/atlas-3.10.1-gcc-4.4.6-nehalem
module load libraries/atlas-3.10.1-gcc-4.4.6-opteron
module load libraries/atlas-3.10.1-gcc-4.4.6-quad

make clean
make nehalem

mprun.sh --job-name SimpleNehalem-N --queue ibm-nehalem.q \
	--script exec_simple.sh --show-qsub --show-script --batch-job
mprun.sh --job-name OptimizedNehalem-N --queue ibm-nehalem.q \
	--script exec_optimized.sh --show-qsub --show-script --batch-job


make clean
make opteron

mprun.sh --job-name SimpleOpteron-N --queue ibm-opteron.q \
	--script exec_simple.sh --show-qsub --show-script --batch-job
mprun.sh --job-name OptimizedOpteron-N --queue ibm-opteron.q \
	--script exec_optimized.sh --show-qsub --show-script --batch-job


make clean
make quad

mprun.sh --job-name SimpleQuad-N --queue ibm-quad.q \
	--script exec_simple.sh --show-qsub --show-script --batch-job
mprun.sh --job-name OptimizedQuad-N --queue ibm-quad.q \
	--script exec_optimized.sh --show-qsub --show-script --batch-job

