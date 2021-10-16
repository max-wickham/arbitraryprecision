#!/bin/bash
python3 ./scripts/test_generator.py
g++ ./generated/tests.cpp ../bigint.hpp -o ./bin/test.o
touch ./output/output.txt
./bin/test.o > ./output/output.txt
cat < ./output/output.txt