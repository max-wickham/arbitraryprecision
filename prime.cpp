#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){
    cout << "hello";
    BigInt a;
    a.rand(37);
    int guess = 0;
    while(!a.prime()){
        cout << "Guess: " << guess << endl;
        //a.print();
        a.rand(37);
    }
    cout <<"Prime"<<endl;
    a.print();

}