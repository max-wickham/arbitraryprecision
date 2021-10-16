#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <iostream>
#include <random>
using namespace std;

const unsigned long int one = 1;
//const int max_pow = 16;
const int max_pow = 32;
const unsigned int max_mask = ((unsigned long int)(one << max_pow) - one);

class BigInt{

    bool negative = false;
    int size;
    vector<unsigned int> digits;

    void flatten();

    public: 

    int max_bit ();
    bool even ();

    //Random number generation

    // Generate a random number up to a given number of bits
    void random(int numBits);
    // Generate a random number up to a given size
    void random(const BigInt &maximum);

    //Bitwise Operators

    void  bitwise_and_self(const BigInt &b); //unfinished
    void  bitwise_or_self(const BigInt &b); //unfinished
    void  bitwise_xor_self(const BigInt &b); //unfinished
    void  bitwise_not_self(); //unfinished
    
    //Comparators
    
    bool equal (const BigInt &b) const;
    bool equal (int b) const;
    bool greater_than(const BigInt &b) const;
    bool greater_than(const int &b) const;
    bool greater_than_equal (const BigInt &b) const; //unfinished
    bool less_than (const BigInt &b) const;
    bool less_than_equal (const BigInt &b) const;

    //Shifting

    void shift_right_self(int x);
    void shift_left_self(int x);
    BigInt shift_right(int x); //unfinished
    BigInt shift_left(int x); //unfinished

    //Addition and Subtraction

    void subtraction_self_unsigned(const BigInt &b);
    void subtraction_self(const BigInt &b);
    void subtraction_self_unsigned(const int &b);
    void subtraction_self(const int &b);
    BigInt subtraction(const BigInt &b);
    BigInt subtraction(const int &b);
    void addition_self_unsigned(const BigInt &b);
    void addition_self(const BigInt &b);
    void addition_self_unsigned(const int &b);
    void addition_self(const int &b);
    BigInt addition(const BigInt &b);
    BigInt addition(const int &b);

    //Multiplication, Division and Modulus
    
    void multiplication(BigInt &b, BigInt &c);
    void multiplication_self(const BigInt &b);
    BigInt multiplication(const BigInt &b);
    void division_self(const unsigned int b);
    void division_self(const BigInt &b);
    void modulus_self(const BigInt &b);
    unsigned int modulus(const int &b);
    BigInt modulus(const BigInt &b);
    BigInt modulo_pow(BigInt e, const BigInt &m);

    //Encryption functions

    bool is_prime(int k);
    BigInt gcd(BigInt const &b) const;
    BigInt moduler_multiplicative_inverse(BigInt m);

    //Printing

    void print() const;
    std::string toString() const;

    //Constructors

    BigInt();
    BigInt (const vector<unsigned int> &_digits);
    BigInt (vector<unsigned int> _digits, bool _negative);

//Operators

    //Comparators
    
    bool operator == (const int &b);
    bool operator == (const BigInt &b);
    bool operator >(const BigInt &b);
    void operator +=(BigInt &b);

    //Addition and Subtraction

    void operator -= (const BigInt &b);
    void operator -= (const int &b);
    BigInt operator - (const BigInt &b);
    BigInt operator - (const int &b);
    void operator += (const BigInt &b);
    void operator += (const int &b);
    BigInt operator + (const BigInt &b);
    BigInt operator + (const int &b);

     //Multiplication, Division and Modulus

    void operator *= (const BigInt &b);
    void operator %= (const BigInt &b);
    BigInt operator * (const BigInt &b);
};

#endif