#!/bin/bash
g++ -W example.cpp -I ../include -I ../src ../src/bigint.cpp -o ./test.o
./test.o
rm test.o