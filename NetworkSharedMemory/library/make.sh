# !/bin/bash
cd obj/
gcc -Wall -c ../src/*.c
ar r ../lib/libMPR.a *.o
ranlib ../lib/libMPR.a