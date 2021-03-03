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

Keys generateKey(BigInt primeP, BigInt primeQ){
    Keys keys;
    BigInt n;
    n.multiplication(primeP,primeQ);
    //n = p*q
    BigInt ctf;
    ctf.totient(primeP,primeQ);
    //choose a number e less than ctf that is coprime to it
    int bits = ctf.max_bit();
    BigInt e;
    e.random(bits);
    while(!(ctf.modulus(e) == 0)){
        e.random(bits);
    }
    //fnd the modular multiplicative inverse of e, d
    BigInt d = e.moduler_multiplicative_inverse(ctf);
    //e is the public key. d is the private key
    keys.privateKey = d;
    keys.publicKey = e;
    keys.n = n;
    return keys; 
}

BigInt encrypt(BigInt message, BigInt key, BigInt n){
    BigInt result = message;
    result.modulo_pow(key,n);
    return result;
}