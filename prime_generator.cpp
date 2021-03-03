#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "bigint.hpp"
#include <chrono>
using namespace std;

int main(){

    BigInt a;
    a.random(1000);
    a.print();
    cout << a.toString();
    int count = 1;
    while(!a.is_prime(10)){
        a.random(1000);
        if(a.even()){
            a.addition_self_unsigned(1);
        }
        cout << a.toString() << endl;
        count++;
        cout << "count " << count << endl; 
    }
    cout << "count " << count;

}//326315851429
//3963671696971241929295694384568056196994712893237947606755647028577828121899124175986131700842687892587698069367023470202953829203866952510165779336888168188639623439814940799535142252572709413605146844235765056229809382198164115720461348409139260381544685505681100896203471460903742930421906539148899