g++ tests.cpp ../bigint.hpp -o ../bin/test.o
touch ../output/output.txt
../bin/test.o > ../output/output.txt