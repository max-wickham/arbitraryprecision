#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "bigint.hpp"
#include "rsa.cpp"
#include <chrono>
using namespace std;

int main(){

    BigInt a;
    a.random(312);
    int count = 1;
    while(!a.is_prime(10)){
        a.random(312);
        if(a.even()){
            a.addition_self_unsigned(1);
        }
        count++;
        //cout << "count " << count << endl; 
    }
    //cout << a.toString() << endl;
    BigInt b;
    b.random(313);
    count = 1;
    while(!b.is_prime(10)){
        b.random(313);
        if(b.even()){
            b.addition_self_unsigned(1);
        }
        count++;
        //cout << "count " << count << endl; 
    }
    //cout << a.toString() <<endl;
    //cout << b.toString() <<endl;
    Keys key = generateKey(a,b);
    //key.privateKey.print();
    //key.publicKey.print();
    //key.n.print();
    BigInt message({134,123,987});
    BigInt encrypted_message = encrypt(message,key.privateKey,key.n);
    BigInt decrypted_message = encrypt(encrypted_message,key.publicKey,key.n);
    //cout << key.publicKey.toString() << endl;
    //cout << key.privateKey.toString() << endl;
    cout << "Message: ";
    message.print();
    cout << "Encrypted Message: ";
    encrypted_message.print();
    cout << "Decrypted Message: ";
    decrypted_message.print();
}
