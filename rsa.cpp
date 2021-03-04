#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "bigint.hpp"
#include <chrono>
using namespace std;

struct Keys{
    BigInt privateKey;
    BigInt publicKey;
    BigInt n;
};

BigInt totient(BigInt &PrimeP, BigInt &PrimeQ){
    //find lowest common factor of p-1 and q-1
    BigInt p = PrimeP;
    BigInt q = PrimeQ;
    p.subtraction_self_unsigned(1);
    //p.print();
    q.subtraction_self_unsigned(1);
    //q.print();
    BigInt gcd = p.gcd(q);
    //gcd.print();
    BigInt result;
    q.multiplication(p,result);
    result.division_self(gcd);
    return result;
}

Keys generateKey(BigInt primeP, BigInt primeQ){
    Keys keys;
    BigInt n;
    primeQ.multiplication(primeP,n);
    //n = p*q
    BigInt ctf;
    ctf = totient(primeP,primeQ);//shoudl be lcm of primeP-1 and primeQ-1#####
    //choose a number e less than ctf that is coprime to it
    int bits = ctf.max_bit();
    BigInt e;
    e.random(bits-10);
    while((!e.is_prime(6)) & (!(ctf.modulus(e) == 0))){
        e.random(bits);
    }//e should be coprime to ctf ########
    //find the modular multiplicative inverse of e, d
    BigInt d = e.moduler_multiplicative_inverse(ctf);//check valid d#####
    //e is the public key. d is the private key
    keys.privateKey = e;
    keys.publicKey = d;
    keys.n = n;
    return keys; 
}

BigInt encrypt(BigInt message, BigInt key, BigInt n){
    BigInt result = message;
    result = result.modulo_pow(key,n);
    return result;
}