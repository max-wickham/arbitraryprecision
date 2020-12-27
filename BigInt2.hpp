#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <deque>
#include <chrono>
#include <chrono>
#include <cstring>
#include <algorithm>   
using namespace std;

const int one = 1;
const int max_pow = 16;
const long long int max_int = (one << max_pow);
const long long int max_mask = (one << max_pow) - 1;
const int base = pow(2,max_pow);

class BigInt{
    bool negative = false;
    int size = 0;
    vector<unsigned int> digits;
    
    // static const int one = 1;
    // static const int max_pow = 16;
    // static const long long int max_int = (one << max_pow);
    // static const long long int max_mask = (one << max_pow) - 1;
    
    bool greater(const BigInt &b){
        return true;
    }
    bool operator >(const BigInt &b){
        if(b.size != size){
            return b.size > size;
        }
        for(int i = size - 1; i >= 0; i--){
            if(digits[i] != b.digits[i]){
                return digits[i] > b.digits[i];
            }
        }
        return false;
    }

    void subtraction(const BigInt &b){
        return;
    }
    void addition(const BigInt &b){
        unsigned int carry = 0;
        int i;
        if(size >= b.size){
            for(i = 0; i < b.size; i++){
                carry += digits[i] + b.digits[i];
                digits[i] = carry & max_mask;
                carry >>= max_pow;
            }
            for(; i < size; i++){
                carry += digits[i];
                digits[i] = carry & max_mask;
                carry >>= max_pow;
                if(!carry){break;}
            }
            if(carry){
                digits[i] = carry;
                size++;
            }
        }else{
            for(i = 0; i < size; i++){
                carry += digits[i] + b.digits[i];
                digits[i] = carry & max_mask;
                carry >>= max_pow;
            }
            for(; i < b.size; i++){
                carry += b.digits[i];
                digits.push_back(carry & max_mask);
                carry >>= max_pow;
            }
            size = b.size;
            if(carry){
                digits[i] = carry;
                size++;
            }
        }
    }
    void multiplication(BigInt &b, BigInt &c){
        // vector<BigInt> pows;
        // BigInt result;
        // BigInt mult;
        // mult.digits = {0,0};
        // unsigned int carry = 0;
        // int j=0;
        // for(int i=0; i<b.size; i++){
        //     for(j=0; j<size; j++){ //36
        //         //mult.digits = {}; // 4
        //         //it += (i+j);
        //         mult.size = 2 + i + j; 
        //         carry = b.digits[i] * digits[j]; //9
        //         mult.digits[0] = carry & max_mask; //50
        //         mult.digits[1] = carry >> max_pow;
        //         //  //60
        //         auto it = mult.digits.end();
        //         mult.digits.insert(it,0,i+j);
        //         result.addition(mult); //200
        //     }
        // }
        // return result;
        //c.digits = vector<unsigned int>(size+b.size+1,0);
        //fill(c.digits.begin(),c.digits.end(),0);
        c.digits.clear();
        c.digits.resize(size+b.size+1,0);
        unsigned int carry = 0;
        unsigned int mult;
        for(int i=0; i < size; i++){
            for(int j=0; j < b.size; j++){
                mult = c.digits[i+j] + digits[i] * b.digits[j] + carry;
                c.digits[i+j] = mult && max_mask;
                carry = mult >> max_pow;
            }
            if(carry){
                mult = carry;
                c.digits[i+b.size] = mult && max_mask;
            }

            carry = 0;
        }
        while (c.digits.size() > 1 && c.digits.back() == 0){
            c.digits.pop_back();
        }
        c.size = c.digits.size();
    }   
    public: 
    BigInt(){}
    BigInt (vector<unsigned int> _digits){
        digits = _digits;
        size = digits.size();
    }

    void operator +=(BigInt &b){
        if(b.negative){
            if(negative){
                this->addition(b);
            }else{
                if(greater(b)){
                    BigInt c;
                    c = b;
                    c.subtraction(*this);
                    *this = c;
                    negative = true;
                }else{
                    this->subtraction(b);
                }
            }
        }else{
            if(negative){
                if(greater(b)){
                    BigInt c;
                    c = b;
                    c.subtraction(*this);
                    *this = c;
                    negative = false;
                }
            }else{
                    this->addition(b);
            }
        }
    }
    // BigInt operator *(BigInt &b){
    //     return multiplication(b,b);
    // }
};
