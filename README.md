# This is a Python Library for Encryption built with C++

## BigInt 
- The project contains a custom bigint class implementation
- The class is found in the file bigint.hpp in "./include" and the implementation is found in "./src/bigint.cpp"
- The class also implements an algorithm for generating large prime numbers

## Testing BigInt
- Tests can be run by running test.sh script in the test folder, the output can be found in the output folder in the test folder. At the moment some test still need to be implemented. 
  
## Building Python Library
- Running **"python3 setup.py build"** from within the "src" folder will build the python library, the .so file can be found in the build folder
- Running **"python3 setup.py install"** from within the "src" folder will install the python library locally
- The library is named encryption and can be imported using "import encryption"
  
## Python Functions
- the encryption library contains the following funcitons
  - **generatePrime(n)**, return a prime int of bit length n or less

## Encryption Functions
  - The file encryption.cpp contains functions for both generating RSA encryptoin keys from prime numbers and a function for encryption and decryption. These functions are working in C++ but haven't been connected to the python library yet. 