#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){
    int n = 29;
    cout << "Starting" << endl;
    BigInt a;
    BigInt b;
    BigInt c;

    
    //BigInt test({1832});
    //test.shift_left_self(29);
    // //auto start = chrono::steady_clock::now();
    a.random(n);
    //a.print();
    // auto end = chrono::steady_clock::now();
    // cout << "Rand Time Time : "
    //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
    //     <<" ns" <<endl;
    for(int x = 5; x < 30; x++){
        auto start = chrono::steady_clock::now();
        //BigInt b({764 ,61815});
        //bool prime = b.is_prime(6);
        //cout << "Prime: " << prime << endl;
        for(int i = 0; i < 100; i++){
            //a.random(x);
            //a.is_prime(6);
            a.random(x);
            a.addition_self_unsigned(1);
            b.random(x);
            c.random(x);
            a.print();
            b.print();
            c.print();
            // //b.modulo_pow(c,a);
            // c.shift_right_self(1);
            // b.multiplication_self(b);
            b.modulo_pow(c,a);
            //a = b;
        }
        auto end = chrono::steady_clock::now();
        cout // << "Prime Time : "
            << chrono::duration_cast<chrono::nanoseconds>(end-start).count() <<endl;
        //  <<" ns" <<endl;   
    }
    int guess = 0;

    //BigInt x({1385,32411});
    //BigInt y({1,0,0});
    //y.modulus_self(x);


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


    // while(!a.is_prime(6)){
    //     //cout << "Running" << endl;
    //     a.random(n);
    //     a.shift_left_self(1);
    //     a.addition_self_unsigned(1);
    //     if(guess % 100 == 0){
    //         cout << "Guess: " << guess << endl;
    //         a.print();
    //     }
    //     //a.print();
    //     guess++;
    // }
    // cout << "Guesses " << guess << endl;
    // cout <<"Prime"<<endl;
    // a.print();

}