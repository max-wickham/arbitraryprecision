#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <deque>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <cstdlib>   
using namespace std;

const unsigned int one = 1;
const int max_pow = 16;
const unsigned int max_int = (one << max_pow);
const unsigned int max_mask = (one << max_pow) - 1;

//max bit constants
const unsigned int left = 65280;
const unsigned int left_right_left = 3072;
const unsigned int left_right_left_left = 2048;
const unsigned int left_right_right_left = 512;
const unsigned int left_left = 61440;
const unsigned int left_left_left = 49152;
const unsigned int left_left_left_left = 32768;
const unsigned int left_left_right_left = 8192;
const unsigned int right_left = 240;
const unsigned int right_left_left = 192;
const unsigned int right_right_left = 12;
const unsigned int right_left_left_left = 128;
const unsigned int right_left_right_left = 32;
const unsigned int right_right_left_left = 8;
const unsigned int right_right_right_left = 2;
 
//const int base = pow(2,max_pow);

class BigInt{

    bool negative = false;
    int size;
    vector<unsigned int> digits;

    void flatten(){
        this->size = this->digits.size();
        while((digits[this->size - 1] == 0) && (this->size > 1)){
            this->digits.erase(this->digits.end() -1);
            this->size--;
        }
    }

    int max_bit (){
        this->flatten();

        if(size == 0){
            return 0;
        }

        unsigned int num = this->digits[this->size-1];
        int result =  (this->size - 1) * max_pow;
        // while((num & max_mask)){
        //     result++;
        //     num >>= 1;
        // }
        // return result;
        if(num & 65280u){
            if(num & left_left){
                if(num & left_left_left){
                    return ((num & left_left_left_left)?16:15 + result);      
                }else{
                    return ((num & left_left_right_left)?14:13 + result);
                }
            }else{
                if(num & left_right_left){
                    return ((num & left_right_left_left)?12:11) + result;      
                }else{
                    return ((num & left_right_right_left)?10:9) + result;
                }
            }
        }else{
            if(num & right_left){
                if(num & right_left_left){
                    return ((num & right_left_left_left)?8:7) + result;      
                }else{
                    return ((num & right_left_right_left)?6:5) + result;
                }
            }else{
                if(num & right_right_left){
                    return ((num & right_right_left_left)?4:3) + result;      
                }else{
                    return ((num & right_right_right_left)?2:1) + result;
                }
            }
        }

    }

    public: 
    
    //Random number generation

    void random(int bits){
        digits.clear();
        size = 0;

        while(bits >= max_pow){
            digits.push_back(rand() & max_mask);
            bits -= max_pow;
        }
        if(bits != 0){
            int mask = (1 << bits) - 1;
            this->digits.push_back(rand() & mask);
        }
        this->size = this->digits.size();
        this->flatten();
    }
    
    void random(const BigInt &maximum){
        this->digits.clear();
        for(int i = 0; i < maximum.size - 1; i++){
            digits.push_back((rand() & max_mask));
        }
        digits.push_back(((rand()&max_mask) % maximum.digits[maximum.size - 1]));
    }
    
    //Bitwise Operators

    void  bitwise_and_self(const BigInt &b); //unfinished

    void  bitwise_or_self(const BigInt &b); //unfinished

    void  bitwise_xor_self(const BigInt &b); //unfinished

    void  bitwise_not_self(); //unfinished
    
    //Comparators

    bool equal (const BigInt &b){
        if(this->size != b.size){
            return false;
        }
        for(int i = 0; i < this->size; i++){
            if(this->digits[i] != b.digits[i]){
                return false;
            }
        }
        return true;
    }

    bool equal (int b){
        if(size != 1){
            return false;
        }
        return this->digits[0] == b;
    }

    bool greater_than(const BigInt &b){
        if(b.size != this->size){
            bool x = (b.size < this->size);
            return (b.size < this->size);
        }
        for(int i = this->size - 1; i >= 0; i--){
            if(this->digits[i] != b.digits[i]){
                return this->digits[i] > b.digits[i];
            }
        }
        return false;
    }
    
    bool greater_than_equal (const BigInt &b); //unfinished

    bool less_than (const BigInt &b){
        if(size != b.size){
            return b.size > size;
        }
        for(int i = size - 1; i >= 0; i--){
            if(b.digits[i] != digits[i]){
                return b.digits[i] > digits[i];
            }
        }
        return false;
    }

    bool less_than_equal (const BigInt &b){
        if(size != b.size){
            return b.size > size;
        }
        for(int i = size - 1; i >= 0; i++){
            if(b.digits[i] != digits[i]){
                return b.digits[i] > digits[i];
            }
        }
        return true;
    }
    
    //Shifting

    void shift_right_self(int x){
        // this->flatten(); //shouldnt be needed
        // int size = this->digits.size();

        while(x >= max_pow){
            this->digits.erase(this->digits.begin());
            x -= max_pow;
        }
        int mask = (1 << (x)) - 1;
        for(int i = 0; i <  this->size - 1; i++){
             this->digits[i] =  (this->digits[i] >> x) +  ((this->digits[i+1] & mask) << (max_pow - x));
        }
        this->digits[size - 1] = this->digits[size - 1] >> x;

        this->flatten();
        size = digits.size();
    }

    void shift_left_self(int x){
        this->flatten();

        this->digits.push_back(0);
        this->size += 1;
        int count = 0;
        while(x >= max_pow){
            count ++;
            //this->digits.erase(this->digits.begin());
            //this->digits.push_front(0);
            x -= max_pow;
        }
        if(count != 0){
            this->size += count;
            vector<unsigned int> zeros(count,0);
            for(auto i: this->digits){
                zeros.push_back(i);
            }
            //zeros.insert(zeros.end(), this->digits.begin(), this->digits.end()); 
            this->digits = zeros;
        }
        int mask = max_mask - ((1 << (max_pow - x)) - 1);
        for(int i = this->size - 1; i >  0; i--){
             this->digits[i] =  ((this->digits[i] << x) & max_mask)  +  ((this->digits[i-1] & mask) >>  (max_pow - x));
        }
        this->digits[0] = ((this->digits[0] << x) & max_mask);

        this->flatten();
    }

    BigInt shift_right(int x); //unfinished

    BigInt shift_left(int x); //unfinished

    //Addition and Subtraction

    void subtraction_self_unsigned(const BigInt &b){
        int carry = 0;
        int i;
        int digitandcarry;
        for(i = 0; i < b.size; i++){
            digitandcarry = digits[i] - carry;
            bool temp = ((digitandcarry) < (int)b.digits[i]);
            digits[i] = (((1 << max_pow) + digits[i] - carry - b.digits[i]) & max_mask);
            carry = temp;
        }
        for(; i < this->size; i++){
            //carry += digits[i];
            if(!carry){break;}
            digitandcarry = digits[i] - carry;
            bool temp = (digitandcarry) < 0;
            digits[i] = ((1 << max_pow) + digitandcarry) & max_mask;
            carry = temp;
        }

        this->flatten();
    }

    void subtraction_self(const BigInt &b){
        if(this->greater_than(b)){
            if(this->negative){
                if(b.negative){
                    this->subtraction_self_unsigned(b);
                }else{
                    this->addition_self_unsigned(b);
                }
            }else{
                if(b.negative){
                    this->addition_self_unsigned(b);
                }else{
                    this->subtraction_self_unsigned(b);
                }
            }
        }else{
            if(this->negative){
                if(b.negative){
                    BigInt temp = b;
                    temp.subtraction_self_unsigned(*this);
                    *this = temp;
                    this->negative = !this->negative;
                }else{
                    this->addition_self_unsigned(b);
                }
            }else{
                if(b.negative){
                    this->addition_self_unsigned(b);
                }else{
                    BigInt temp = b;
                    temp.subtraction_self_unsigned(*this);
                    *this = temp;
                    this->negative = !this->negative;
                }
            }
        }
    }

    void subtraction_self_unsigned(const int &b){
        int carry = 0;
        int digitandcarry;
        int i = 1;
        digitandcarry = digits[0] - carry;
        bool temp = (digitandcarry) < b;
        digits[0] = ((1 << max_pow) + digitandcarry - b) & max_mask;
        carry >>= temp;
        
        for(; i < this->size; i++){
            carry += digits[i];
            digitandcarry = digits[i] - carry;
            bool temp = (digitandcarry) >= 0;
            digits[i] = ((1 << max_pow) + digitandcarry) & max_mask;
            carry = temp;
            if(!carry){break;}
        }

        this->flatten();
        this->size = digits.size();
    }
    
    BigInt subtraction(const BigInt &b); //unfinished
    
    void addition_self_unsigned(const BigInt &b){
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

        this->flatten();
        size = digits.size();
    }
    
    void addition_self_unsigned(const int &b){
        if(this->size == 0){
            this->size = 1;
            digits.push_back(0);
        }
        unsigned int carry = 0;
        carry += digits[0] + b;
        digits[0] = carry & max_mask;
        carry >>= max_pow;
        int i = 1;
        for(; i < this->size; i++){
            carry += digits[i];
            digits[i] = carry & max_mask;
            carry >>= max_pow;
            if(!carry){break;}
        }
        if(carry){
            digits[i] = carry;
            this->size++;
        }
        this->flatten();
        this->size = digits.size();
    }
    
    BigInt addition(const BigInt &b); //unfinished

    //Multiplication, Division and Modulus
    
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
        //while (c.digits.size() > 1 && c.digits.back() == 0){
        //    c.digits.pop_back();
        //}
        c.flatten();
        c.size = c.digits.size();
    }   

    void multiplication_self(BigInt &b){
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
        if(this->size == 1){
            if(this->digits[0] == 0){
                return;
            }
        }
        BigInt c;
        c.digits.clear();
        c.digits.resize(size+b.size+1,0);
        unsigned int carry = 0;
        unsigned int mult;
        for(int i=0; i < this->size; i++){
            for(int j=0; j < b.size; j++){
                mult = c.digits[i+j] + this->digits[i] * b.digits[j] + carry;
                c.digits[i+j] = (mult & max_mask);
                carry = mult >> max_pow;
            }
            if(carry){
                mult = carry;
                c.digits[i+b.size] = (mult & max_mask);
            }

            carry = 0;
        }
        //while (c.digits.size() > 1 && c.digits.back() == 0){
        //    c.digits.pop_back();
        //}
        c.flatten();
        c.size = c.digits.size();
        *this = c;
    }   
    
    void modulus_self(const BigInt &b){
        BigInt divisor = b;
        if(divisor.greater_than(*this)){
            return;
        }
        //BigInt result = *this;   13620 45525
        int max_bit_divisor = divisor.max_bit();
        int max_bit = this->max_bit();

        divisor.shift_left_self(max_bit - max_bit_divisor);
        max_bit_divisor = max_bit;
        //BigInt temp;
        //while(this->greater_than(b)){
        while(true){
            //temp = *this;
            //temp.subtraction_self_unsigned(divisor);
            if(divisor.greater_than(*this)){
                max_bit_divisor -= 1;
                divisor.shift_right_self(1);
            }else{
                this->subtraction_self_unsigned(divisor);
                if(!this->greater_than(b)){
                    break;
                }
                max_bit = this->max_bit();
                divisor.shift_right_self(max_bit_divisor - max_bit);
                max_bit_divisor = max_bit;
            }
        }
    }


    unsigned int modulus(const int &b){
        vector<unsigned int> _digits = this->digits;
        if(this->size == 0){
            return 0;
        }
        _digits[this->size -1] = _digits[this->size - 1] % b;
        int max_int_modulo = max_int % b;
        for(int i = this->size - 2; i >= 0; i--){
            _digits[i] = ((_digits[i] % b) + ((_digits[i+1] * max_int_modulo) % b)) % b;
        }

        return _digits[0];
    }

    BigInt modulus(const BigInt &b){
        BigInt divisor = b;
        BigInt result = *this;
        int max_bit_divisor = divisor.max_bit();
        int max_bit = this->max_bit();

        divisor.shift_right_self(max_bit - max_bit_divisor);
        max_bit_divisor = max_bit;
        BigInt temp;
        while(result.greater_than(b)){
            temp = result;
            temp.subtraction_self_unsigned(divisor);
            if(temp.negative){
                max_bit_divisor -= 1;
                divisor.shift_right_self(1);
            }else{
                result = temp;
                max_bit = this->max_bit();
                divisor.shift_left_self(max_bit_divisor - max_bit);
                max_bit_divisor = max_bit;
            }
        }
        return result;
    }
    
    BigInt modulo_pow(BigInt e, const BigInt &m){

        BigInt result({1});
        BigInt b = *this;

        if(b.digits.size() == 1){
            if(b.digits[0] == 0){
                return b;
            }
        }
        b.modulus_self(m);

        BigInt zero({0});
        while(e > zero){
            //if(e.num_vec[e.num_vec.size()-1]%2 == 1){
            //if(e.digits[e.digits.size()-1]&1){    
            if(e.digits[0]&1){    
                //result = (result * b) % m;
                result.multiplication_self(b);
                result.modulus_self(m);
            }
            //e = e >> 1;
            e.shift_right_self(1);
            b.multiplication_self(b);
            //b.print();
            //m.print();
            b.modulus_self(m);
            //b = (b * b) % m;
        }
        return result;
    }

    //Prime Number functions

    bool is_prime(int k){
        BigInt n = *this;
        //cout << n.size << endl;
        if(this->size == 0){
            return false;
        }
        if(this->size == 1){
            if(this->digits[0] == 1){
                return false;
            } 
            if(this->digits[0] == 0){
                return false;
            }           
        }
        if(this->modulus(3) == 0){
                return false;
        } 
        if(this->modulus(5) == 0){
                return false;
        }
        BigInt _n;
        _n = n;
        _n.subtraction_self_unsigned(1);
        BigInt s;
        BigInt r;
        r = n;
        r.subtraction_self_unsigned(1);
        int test = 15 & 1;
        //bool test = r.digits[0]&1;
        while(!(r.digits[0]&1)){
            s.addition_self_unsigned(1);
            r.shift_right_self(1);
            //r.print();
        }
        for(int i=0; i < k; i++){
            //cout << "i " << i <<  endl;
            //auto start = chrono::steady_clock::now();
            BigInt a;
            a.random(_n);
            //auto end = chrono::steady_clock::now();
            BigInt x;
            //a.print();
            x = a.modulo_pow(r,n);
            //cout << "In Prime" << endl;
            if((!(x.equal(1))) && (!(x.equal(_n)))){
                BigInt j;
                j.addition_self_unsigned(1);
                while((j.less_than(s)) && !(x.equal(_n))){
                    x.multiplication_self(x);
                    x.modulus_self(n);
                    if(x.equal(1)){
                        //cout << "Leaving" << endl;
                        return false;
                    } 
                    j.addition_self_unsigned(1);
                }
                if(!(x.equal(_n))){
                    //cout << "Leaving" << endl;
                    return false;
                }
            }
        }
        //cout << "Leaving" << endl;
        return true;
    }

    //Printing

    void print() const{
        BigInt temp = *this;
        string result = "";
        cout << "Size: " << size << endl;
        for(int i = size - 1; i > 0; i--){
            cout << digits[i] << " ";
        }
        cout << digits[0];
        cout << result;
        cout << endl;
    }
   
    //Constructors

    BigInt(){
        size = 1;
        digits.push_back(0);
    }
    
    BigInt (vector<unsigned int> _digits){
        for(int i = _digits.size() - 1; i >= 0; i--){
            digits.push_back(_digits[i]);
        }
        //this->digits = _digits;
        this-> negative = false;
        this->flatten();
    }

    BigInt (vector<unsigned int> _digits, bool _negative){
        //digits = _digits;
        for(int i = _digits.size() - 1; i >= 0; i--){
            digits.push_back(_digits[i]);
        }
        this->flatten();
        negative = _negative;
    }

    //Operators

    bool operator >(const BigInt &b){
        // if(b.size != size){
        //     return b.size > size;
        // }
        // for(int i = size - 1; i >= 0; i--){
        //     if(digits[i] != b.digits[i]){
        //         return digits[i] > b.digits[i];
        //     }
        // }
        // return false;
        return this->greater_than(b);
    }
    
    void operator +=(BigInt &b){
        if(b.negative){
            if(negative){
                this->addition_self_unsigned(b);
            }else{
                if(greater_than(b)){
                    BigInt c;
                    c = b;
                    c.subtraction_self_unsigned(*this);
                    *this = c;
                    negative = true;
                }else{
                    this->subtraction_self_unsigned(b);
                }
            }
        }else{
            if(negative){
                if(greater_than(b)){
                    BigInt c;
                    c = b;
                    c.subtraction_self_unsigned(*this);
                    *this = c;
                    negative = false;
                }
            }else{
                    this->addition_self_unsigned(b);
            }
        }
    }

};
