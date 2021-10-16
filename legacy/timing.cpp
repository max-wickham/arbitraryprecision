#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){
    for(int j = 10; j < 100; j++){
        auto start = chrono::steady_clock::now();
        vector<unsigned int> a_vec;
        vector<unsigned int> b_vec;
        for(int a=0; a<j; a++){
            a_vec.push_back(2);
            b_vec.push_back(7);
        }
        BigInt a(a_vec);
        BigInt b(b_vec);
        BigInt c(b_vec);

        for(int i = 0; i < 100; i ++){
            a.modulo_pow(b,c);
        }

        auto end = chrono::steady_clock::now();
        cout
                << chrono::duration_cast<chrono::milliseconds>(end-start).count()
            <<endl;
    }
}