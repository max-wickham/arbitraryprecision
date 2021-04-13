python3 test_generator.py
g++ tests1.cpp ../bigint.hpp -o ../bin/test.o
touch ../output/output.txt
../bin/test.o > ../output/output.txt
cat < ../output/output.txt