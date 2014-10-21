#
# Author: Pirvulescu Andreea Monica
# 
# CC=gcc
#
CC=gcc
LD_FLAGSn=-lcblas -latlas -lm -lrt -L/opt/tools/libraries/atlas/3.10.1-nehalem-gcc-4.4.6/lib
LD_FLAGSo=-lcblas -latlas -lm -lrt -L/opt/tools/libraries/atlas/3.10.1-opteron-gcc-4.4.6/lib
LD_FLAGSq=-lcblas -latlas -lm -lrt -L/opt/tools/libraries/atlas/3.10.1-quad-gcc-4.4.6/lib

CC_FLAGS=-O3 -mfpmath=sse -fprefetch-loop-arrays

nehalem:
	$(CC) simple_dsymv.c  $(LD_FLAGSn) -Wall -o simple_dsymv
	$(CC) optimized_dsymv.c  $(LD_FLAGSn) -Wall -o optimized_dsymv $(CC_FLAGS)

opteron: 
	$(CC) simple_dsymv.c  $(LD_FLAGSo) -Wall -o simple_dsymv
	$(CC) optimized_dsymv.c  $(LD_FLAGSo) -Wall -o optimized_dsymv $(CC_FLAGS)

quad:
	$(CC) simple_dsymv.c  $(LD_FLAGSq) -Wall -o simple_dsymv
	$(CC) optimized_dsymv.c  $(LD_FLAGSq) -Wall -o optimized_dsymv $(CC_FLAGS)

clean:
	rm -f simple_dsymv optimized_dsymv
	rm -f *.o

