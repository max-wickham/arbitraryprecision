#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "BigInt2.hpp"
#include <chrono>
using namespace std;

int main(){
auto start = chrono::steady_clock::now();

    BigInt a({1,2,3});
    BigInt b({2,3,4});
    BigInt c;

    for(int i = 0; i < 100000; i ++){
        a.multiplication(b,c);
    }



auto end = chrono::steady_clock::now();
cout << "Time : "
        << chrono::duration_cast<chrono::milliseconds>(end-start).count()
        <<" ms" <<endl;
}