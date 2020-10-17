#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){
    cout << "hello";
    BigInt a;
    auto start = chrono::steady_clock::now();
    a.rand(15, start);
    int guess = 0;
    while(!a.prime()){
        cout << "Guess: " << guess << endl;
        //a.print();
        a.rand(15, start);
        a.print();
        guess++;
    }
    cout <<"Prime"<<endl;
    a.print();

}