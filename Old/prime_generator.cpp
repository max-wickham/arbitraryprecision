#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
using namespace std;
#include <chrono>

bool isPrime(BigInt n, int k = 30){
    // BigInt _n;
    // _n = n;
    // _n -= 1;
    // BigInt s;
    // BigInt r;
    // r = n;
    // cout << "running";
    // r -= 1;
    // auto start = chrono::steady_clock::now();
    // while(r.even()){
    //     s += 1;
    //     r >> 1;
    // }
    // auto end = chrono::steady_clock::now();
    // cout << "Elapsed Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;

    // for(int i=0; i < k; i++){
    //     cout << "i " << i <<  endl;
    //     //auto start = chrono::steady_clock::now();
    //     BigInt a;
    //     a.rand(_n);
    //     auto end = chrono::steady_clock::now();
    //     BigInt x;
    //     x = a.modulo_pow(r,n);
    //     if(!(x == 1) && !(x == _n)){
    //         BigInt j;
    //         j += 1;
    //         while((j < s) && !(x == _n)){
    //             x = x * x;
    //             x = x % n;
    //             if(x == 1){
    //                 return false;
    //             } 
    //             j += 1;
    //         }
    //         if(!(x==_n)){
    //             return false;
    //         }
    //     }
    // }
    return true;
}

int main(){
    cout << "hello";
    BigInt a;
    a.rand(37);
    int guess = 0;
    while(!isPrime(a)){
        cout << "Guess: " << guess << endl;
        a.print();
        a.rand(37);
    }
    cout <<"Prime"<<endl;
    a.print();

}
