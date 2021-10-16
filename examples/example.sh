#!/bin/bash
g++ -W example.cpp -I ../include -I ../src ../src/bigint.cpp ../src/rsa.cpp -o ./test.o
./test.o
rm test.o