#include <vector>
#include <cmath>
#include <iostream>
#include "bigint.hpp"
using namespace std;
#include <chrono>

bool isPrime(BigInt n, int k = 30){
    BigInt _n;
    _n = n;
    _n -= 1;
    BigInt s;
    BigInt r;
    //n.print();
    r = n;
    r -= 1;
    //r.print();
    //s.print();
    auto start = chrono::steady_clock::now();
    while(r.even()){
        //r.print();
        s += 1;
        r >> 1;
    }
    auto end = chrono::steady_clock::now();
    cout << "Elapsed Time : "
        << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
        <<" ns" <<endl;

    //s.print();
    //r.print();
    for(int i=0; i < k; i++){
        cout << "i " << i <<  endl;
        //auto start = chrono::steady_clock::now();
        BigInt a;
        a.rand(_n);
        auto end = chrono::steady_clock::now();
        //cout << "Rand Time : "
        //    << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
        //    <<" ns" <<endl;
        //cout << "a ";
        //a.print();
        //cout << "a"<< endl;
        //cout << "2" << endl;
        BigInt x;
        //->x = a.pow(r);
        //cout << "r ";
        //r.print();
        //cout << "x ";
        //x.print();
        //cout << "4" << endl;
        //->x = x.modulo(n);
        //auto start2 = chrono::steady_clock::now();
        x = a.modulo_pow(r,n);
        //auto end2 = chrono::steady_clock::now();
        //cout << "Modulo Time : "
        //    << chrono::duration_cast<chrono::nanoseconds>(end2-start2).count()
        //    <<" ns" <<endl;
        //cout << "3" << endl;
        if(!(x == 1) && !(x == _n)){
            BigInt j;
            j += 1;
            while((j < s) && !(x == _n)){
                x = x * x;
                x = x % n;
                if(x == 1){
                    return false;
                } 
                j += 1;
            }
            if(!(x==_n)){
                return false;
            }
        }
    }
    return true;
}

int main(){
    // BigInt b;
    // b.pow_2(2);
    // a = a.pow(b);
    //a = a*b;
    //b.print();
    //a = a+b;
    // a.print();
    //cout << "hello";
    // a.rand(11);
    // a.print();
    // a.rand(11);
    // a.print();
    // a.rand(11);
    // a.print();
    BigInt a;
    //a.set_vec({1,0,1,1,1,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,1,0,1,
    //0,1,1,1,1,0,1,1,0,1,0,1});
    //a.print();
    //cout << "Prime " << isPrime(a) << endl;
    a.rand(512);
    int guess = 0;
    while(!isPrime(a)){
        cout << "Guess: " << guess << endl;
        a.print();
        a.rand(512);
    }
    cout <<"Prime"<<endl;
    a.print();

}
