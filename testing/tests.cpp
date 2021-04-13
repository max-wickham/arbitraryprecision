#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "../bigint.hpp"
#include <chrono>
using namespace std;


void testMaxBit(){
    {
        BigInt a({58813193,295984736,373413994,712712193,452019750});
        BigInt b({0});
        BigInt c;
        BigInt d({146});
        int x = a.max_bit();
        cout << x << endl;
        bool success = d.equal(x);
        cout << (success ? "\033[32m":"\033[31m") << "MaxBit test0 " << (success ? "Pass":"Fail") << "\033[0m" << endl;
        if(!success){
            a.print(); 
            b.print(); 
            c.print(); 
            d.print();
        }
    }
    int max_pow = 32;
    //test 1
    BigInt a({7,2,3});
    int max_bit = a.max_bit();
    bool success = max_bit == (3+2*max_pow);
    cout << "Test max bit 1 " << (success ? "Pass":"Fail") << endl;

    //test 2
    BigInt c({0,2,3});
    max_bit = c.max_bit();
    success = max_bit == (2+max_pow);
    cout << "Test max bit 2 " << (success ? "Pass":"Fail") << endl;

    cout << endl;
}

void testEqual(){
    //test1
    BigInt a({7,2,3});
    BigInt b({0,7,2,3});
    bool equal = a.equal(b);
    cout << "Test equal 1 " << (equal ? "Pass":"Fail") << endl;

    //test 2
    BigInt c({7,2,3});
    BigInt d({6,2,3});
    equal = !c.equal(d);
    cout << "Test equal 2 " << (equal ? "Pass":"Fail") << endl;

    //test 3
    BigInt e({3});
    equal = e.equal(3);
    cout << "Test equal 3 " << (equal ? "Pass":"Fail") << endl;

    //test 4
    BigInt f({3});
    equal = f.equal(3);
    cout << "Test equal 4 " << (equal ? "Pass":"Fail") << endl;

    cout << endl;
}

int main(){
    testMaxBit();
    testEqual();
}

