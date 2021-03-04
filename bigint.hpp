#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <deque>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <tuple>
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

    public: 

    int max_bit (){
        this->flatten();

        if(size == 0){
            return 0;
        }

        unsigned int num = this->digits[this->size-1];
        int result =  (this->size - 1) * max_pow;

        if(num & 65280u){
            if(num & left_left){
                if(num & left_left_left){
                    int x = (((num & left_left_left_left)?16:15) + result);
                    return x;      
                }else{
                    return ((num & left_left_right_left)?14:13) + result;
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

    bool even (){
        return !(this->digits[0] & 1);
    }
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

    bool greater_than(const BigInt &b) const{
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

    bool greater_than(const int &b){
        if(this->size > 1){
            return true;
        }
        return digits[0] > b;
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
            this->size-=1;
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
        carry = temp;
        
        for(; i < this->size; i++){
            //carry += digits[i];
            digitandcarry = digits[i] - carry;
            bool temp = (digitandcarry) < 0;
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
                digits.push_back(carry);
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
        c.digits.clear();
        c.digits.resize(size+b.size+1,0);
        unsigned int carry = 0;
        unsigned int mult;
        for(int i=0; i < size; i++){
            for(int j=0; j < b.size; j++){
                mult = c.digits[i+j] + digits[i] * b.digits[j] + carry;
                c.digits[i+j] = mult & max_mask;
                carry = mult >> max_pow;
            }
            if(carry){
                mult = carry;
                c.digits[i+b.size] = mult & max_mask;
            }

            carry = 0;
        }
        //while (c.digits.size() > 1 && c.digits.back() == 0){
        //    c.digits.pop_back();
        //}
        c.flatten();
        c.size = c.digits.size();
        c.negative = b.negative != this->negative;
    }   

    void multiplication_self(const BigInt &b){
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
        if(b.negative){
            this->negative = !this->negative;
        }
    }   
    
    void division_self(const int &b){
        if(b<0){
            this->negative = !this->negative;
        }
        if(this->size == 0){
            return;
        }
        unsigned int carry = this->digits[this->size - 1] % b;
        this->digits[this->size -1] = this->digits[this->size - 1] / b;
        int max_int_modulo = max_int % b;
        for(int i = this->size - 2; i >= 0; i--){
            this->digits[i] += (carry << 16);
            carry = this->digits[i] % b;
            this->digits[i] = this->digits[i] / b;
            //_digits[i] = ((_digits[i] % b) + ((_digits[i+1] * max_int_modulo) % b)) % b;
        }
        this->flatten();
    }

    void division_self(const BigInt &b){
        BigInt result;
        BigInt divisor = b;
        if(divisor.greater_than(*this)){
            BigInt zero({0});
            *this = zero;
            if(b.negative){
                this->negative = !this->negative;
            }
            return;
        }
        //BigInt result = *this;   13620 45525
        int max_bit_divisor = divisor.max_bit();
        int max_bit = this->max_bit();
        int shift;
        int o_max_bit_diviser = max_bit_divisor;
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
                //needs to be improved alot
                shift = max_bit_divisor - o_max_bit_diviser;
                BigInt adder({1});
                adder.shift_left_self(shift);
                result.addition_self_unsigned(adder);
                if(!this->greater_than(b)){
                    *this = result;
                    if(b.negative){
                        this->negative = !this->negative;
                    }
                    break;
                }
                max_bit = this->max_bit();
                divisor.shift_right_self(max_bit_divisor - max_bit);
                max_bit_divisor = max_bit;
            }
        }
    
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

        divisor.shift_left_self(max_bit - max_bit_divisor);
        max_bit_divisor = max_bit;
        //BigInt temp;
        while(true){
            // = result;
            //temp.subtraction_self_unsigned(divisor);
            if(divisor.greater_than(result)){
                max_bit_divisor -= 1;
                divisor.shift_right_self(1);
            }else{
                result.subtraction_self_unsigned(divisor);
                if(!result.greater_than(b)){
                    break;
                }
                //result = temp;
                max_bit = result.max_bit();
                divisor.shift_right_self(max_bit_divisor - max_bit);
                max_bit_divisor = max_bit;
            }
        }
        return result;
    }
    
    BigInt modulo_pow(BigInt e, const BigInt &m){
        BigInt result({1});
        BigInt b = *this;
        if(b.equal(0)){
            return b;
        }
        b.modulus_self(m);

        BigInt zero({0});
        while(e > zero){
            if(e.digits[0]&1){    
                result.multiplication_self(b);
                result.modulus_self(m);
            }
            e.shift_right_self(1);
            b.multiplication_self(b);
            b.modulus_self(m);
        }
        return result;
    }

    //Encryption functions

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

    BigInt gcd(BigInt const &b) const{
        BigInt result;
        bool bigger = this->greater_than(b);
        BigInt biggest = (bigger ? *this:b);
        BigInt smallest = (!bigger ? *this:b);
        while(true){
            BigInt remainder = biggest.modulus(smallest);
            if (remainder == 0){
                result = smallest;
                break;
            }
            biggest = smallest;
            smallest = remainder;
        }
        return result;
    }

    void totient(BigInt &PrimeP, BigInt &PrimeQ){
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
        *this = result;
    }

    tuple<BigInt, BigInt, BigInt> extended_gcd(BigInt a, BigInt b)
    {
        if (a == 0) {
            BigInt z({0});
            BigInt o({1});
            return make_tuple(b, z, o);
        }
    
        BigInt gcd, x, y;
    
        // unpack tuple returned by function into variables
        BigInt h = b.modulus(a);
        tie(gcd, x, y) = extended_gcd(h, a);
    
        BigInt temp;
        temp = x;

        b.division_self(a);
        b.multiplication_self(x);
        y.subtraction_self(b);
        x = y;
        y = temp;
        return make_tuple(gcd, x, y);
    }

    void ExtendEuclidian(BigInt a, BigInt b, BigInt &x, BigInt &y){
        // def egcd(a, b):
        //     if a == 0:
        //         return b, 0, 1
        //     else:
        //         gcd, x, y = egcd(b % a, a)
        //         return gcd, y - (b // a) * x, x
        if(a == 0){
            BigInt z({0});
            BigInt o({1});
            x = z;
            y = o;
        }
        else{
            BigInt h = b.modulus(a);
            this->ExtendEuclidian(h,a,x,y);
            // y - (b // a) * x, x
            BigInt temp;
            temp = x;

            b.division_self(a);
            b.multiplication_self(x);
            y.subtraction_self(b);
            x = y;
            y = temp;
        }



        // BigInt oldr = a;
        // BigInt r = b;
        // BigInt olds({1});
        // BigInt s({0});
        // BigInt oldt({0}); 
        // BigInt t({1});
        // BigInt quotient;
        // BigInt temp;
        // BigInt temp2;
        // while(!r.equal(0)){
        //     quotient = oldr;
        //     quotient.division_self(r);
        //     temp2 = r;
        //     quotient.multiplication(r,temp);
        //     r = oldr;
        //     r.subtraction_self(temp);
        //     oldr = temp2;
        //     temp2 = s;
        //     quotient.multiplication(s,temp);
        //     s = olds; s.subtraction_self(temp);
        //     olds = temp2;
        //     temp2 = t;
        //     quotient.multiplication(t,temp);
        //     t = oldt; t.subtraction_self(temp);
        //     oldt = temp2;
        // }
        // x = oldt;
        // y = olds;
    }

    BigInt moduler_multiplicative_inverse(BigInt m){
        // BigInt result;
        // BigInt x;
        // BigInt y;
        // tuple<BigInt,BigInt,BigInt> egcd = extended_gcd(*this,m);
        // //result.ExtendEuclidian(*this,m,x,y);
        // x = get<1>(egcd);
        // y =  get<2>(egcd);
        // cout << "X" <<endl;
        // x.print();
        // cout << "Y" << endl;
        // y.print();
        // x.modulus_self(m);
        // x += m;
        // x.modulus_self(m);
        // result = x;
        // return result;

        BigInt a = *this;
        //BigInt result;
        //result * this == 1 mod(m)
        BigInt m0 = m;
        BigInt y({0});
        BigInt x({1});
 
        if (m == 1){
            BigInt zero({0});
            return zero;
        }
 
        while (a.greater_than(1)) {
            // q is quotient
            BigInt q = a;
            q.division_self(m);
            BigInt t = m;
    
            // m is remainder now, process same as
            // Euclid's algo
            m = a.modulus(m);
            a = t;
            t = y;
            cout << "M" << endl;
            m.print();
            cout << "A" << endl;
            a.print();
            cout << "T" << endl;
            t.print();
    
            // Update y and x
            //y = x - q * y;
            //x = t;
            cout << "Y" << endl;
            y.print();
            cout << "Q" << endl;
            q.print();
            BigInt temp;
            y.multiplication(q,temp);
            cout << "TEMP" << endl;
            temp.print();
            y = x;
            y.subtraction_self(temp);
            x = t;
            cout << "X" << endl;
            x.print();
            cout << "Y" << endl;
            y.print();
        }
        x.print();
        // Make x positive
        if (x.negative){
            x += m0;
        }
    
        return x;
        //return result;
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
   
    std::string toString() const{
        vector<int> digits;
        BigInt a = *this;
        std::string result;
        while(a.greater_than(0)){
            std::string d = std::to_string(a.digits[0]);
            result = d.at(d.size()-1) + result;
            a.division_self(10);
        }
        return result;
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
        for(int i = _digits.size() - 1; i >= 0; i--){
            digits.push_back(_digits[i]);
        }
        this->flatten();
        negative = _negative;
    }

    // BigInt (std::string in){
    //     if(in.size() < 16){
    //         int n = std::stoi(in,NULL,2);
    //         this->digits.push_back(n);
    //         this->flatten();
    //         return;
    //     }
    //     while(in.size() >= 16){
    //         int n = std::stoi(in.substr(in.size()-16,in.size()),NULL,2);
    //         in = in.substr(0,in.size()-16);
    //         this->digits.push_back(n);
    //     }
    //     if(in.size() != 0){
    //         int n = std::stoi(in,NULL,2);
    //         this->digits.push_back(n);
    //     }
    //     this->flatten();
    // }

    //Operators

        //Comparators
    
    bool operator == (const int &b){
        return this->equal(b);
    }

    bool operator == (const BigInt &b){
        return this->equal(b);
    }

    bool operator >(const BigInt &b){
        return this->greater_than(b);
    }
    
    void operator +=(BigInt &b){
        if(b.negative){
            if(negative){
                this->addition_self_unsigned(b);
            }else{
                if(this->greater_than(b)){
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
                if(this->greater_than(b)){
                    this->subtraction_self_unsigned(b);
                }
                else{
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

        //Multiplication, Division and Modulus

    void operator *= (const BigInt &b){
        this->multiplication_self(b);
    }

    void operator %= (const BigInt &b){
        this->modulus_self(b);
    }
};
#endif