#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){
    int n = 34;
    cout << "hello";
    BigInt a;
    auto start = chrono::steady_clock::now();
    a.rand(n, start);
    // auto end = chrono::steady_clock::now();
    // cout << "Rand Time Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;

    // start = chrono::steady_clock::now();
    //bool prime = a.prime();
    // end = chrono::steady_clock::now();
    // cout << "Prime Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;   
    int guess = 0;


    // BigInt d({1,2});
    // BigInt b({4,13421,53});
    // BigInt c({1,1,1,1,1,1,1,1,1,1});
    // start = chrono::steady_clock::now();
    // for(int i = 0; i < 1000; i ++){
    //     c = d * b;
    // }
    // end = chrono::steady_clock::now();
    // cout << "Multiplication Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl; 

    // start = chrono::steady_clock::now();
    // for(int i = 0; i < 1000; i ++){
    //     c += d;
    // }
    // end = chrono::steady_clock::now();
    // cout << "Addition Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;   

    // start = chrono::steady_clock::now();
    // for(int i = 0; i < 1000; i ++){
    //     c.max_bit();
    // }
    // end = chrono::steady_clock::now();
    // cout << "Modulus Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;   


    while(!a.prime()){
        a.rand(n, start);
        if(guess % 100 == 0){
            cout << "Guess: " << guess << endl;
            a.print();
        }
        //a.print();
        guess++;
    }
    cout << "Guesses " << guess << endl;
    cout <<"Prime"<<endl;
    a.print();

}