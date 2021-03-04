#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "bigint.hpp"
#include "rsa.cpp"
#include <chrono>
using namespace std;

int main(){

    // BigInt a({45 ,20208, 54895, 37219, 23275, 64368, 52126, 34745, 2563, 7401, 21691, 23380 ,13007});
    // BigInt m({87, 8894, 16235, 6513 ,30544 ,28031, 61376, 26110 ,28262 ,59077, 10941, 17219 ,27624});
    // BigInt e;
    // e = a.moduler_multiplicative_inverse(m);
    // e.print();


    BigInt a({12,6708,59965,23629,51833,59616,39225});
    //a.random(100);
    //a.print();
    //cout << a.toString() << endl;
    int count = 1;
    while(!a.is_prime(10)){
        a.random(100);
        if(a.even()){
            a.addition_self_unsigned(1);
        }
        //cout << a.toString() << endl;
        count++;
        //cout << "count " << count << endl; 
    }
    BigInt b;
    b.random(101);
    //b.print();
    //cout << b.toString();
    count = 1;
    while(!b.is_prime(10)){
        b.random(101);
        if(b.even()){
            b.addition_self_unsigned(1);
        }
        //cout << b.toString() << endl;
        count++;
        //cout << "count " << count << endl; 
    }
    //cout << a.toString() <<endl;
    //cout << b.toString() <<endl;
    Keys key = generateKey(a,b);
    key.privateKey.print();
    key.publicKey.print();
    key.n.print();
    BigInt message({134,123});
    BigInt encrypted_message = encrypt(message,key.privateKey,key.n);
    encrypted_message.print();
    BigInt decrypted_meddage = encrypt(encrypted_message,key.publicKey,key.n);
    decrypted_meddage.print();

}//326315851429
//3963671696971241929295694384568056196994712893237947606755647028577828121899124175986131700842687892587698069367023470202953829203866952510165779336888168188639623439814940799535142252572709413605146844235765056229809382198164115720461348409139260381544685505681100896203471460903742930421906539148899