#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <deque>
#include <chrono>
using namespace std;

class BigInt {
    //private:
    static const long long one = 1;
    static const int max_pow = 32;
    static const long long int max_int = (one << 32);
    static const long long int max_mask = (one << 32) -1;
    deque<unsigned long long int> num_vec = {0};
    bool negative = false;

    public:
    BigInt(){}
    BigInt (vector<unsigned long long int> _num_vec){
        for(auto x: _num_vec){
            num_vec.push_back(x);
        }
    }
    
    void rand(int n){
        while(n > max_pow){
            num_vec.push_front()
        }
    }
    void flatten(){
        while(!num_vec[0]){
            num_vec.pop_front();
        }
    }
    void set_vec(deque<unsigned long long int> vec){
        num_vec = vec;
    }
    void print(){
        for(int i = 0; i < num_vec.size(); i++){
            cout << " " << num_vec[i];
        }
        cout <<endl;
    }
    bool even(){
        return !(num_vec[num_vec.size()-1] & 1);
    }
    //returns the position of the msb 
    int max_bit(){
        this->flatten();
        //this->print();
        //cout <<endl;
        num_vec[0] = num_vec[0] & max_mask;
        //this->print();
        //cout <<endl;
        //cout << max_mask;
        //cout <<endl;
        unsigned long long int bits = num_vec[0];
        int n = max_pow;
        while(!(bits & (one << (n -1) ) ) ){
            n -= 1;
        }
        return (n + (num_vec.size()-1) * max_pow);
    }
    //working
    BigInt operator <<(int n){
        BigInt result;
        result.num_vec = num_vec;
        int size = result.num_vec.size();

        //add a 0 untill n is less than max pow
        while(n > max_pow){
            result.num_vec.push_back(0);
            n -= max_pow; 
        }

        long long int mask = (one << n)-1;
        long long int reverse_mask = mask << (max_pow - n);

        //check for overflow in the biggest int and add overflow to a new entry
        if(result.num_vec[0] >= pow(2,max_pow-n)){
            result.num_vec.push_front(result.num_vec[0] >> (max_pow-n));
        }
        //shift each number by n and add overflow bits from number to the right
        for(int i=0; i <size-1; i++){
            result.num_vec[i] = result.num_vec[i] << n;
            //result.num_vec[i] += result.num_vec[i+1] & mask;
            cout << "i" << i << " " << ((result.num_vec[i+1] & reverse_mask) >> (max_pow -n)) << endl;
            cout << "reverse " << reverse_mask <<endl;
            result.num_vec[i] += (result.num_vec[i+1] & reverse_mask) >> (max_pow - n);
            //remove extra bits
            result.num_vec[i] = result.num_vec[i] & max_mask;
        }
        result.num_vec[size-1] = result.num_vec[size-1] << n;
        result.num_vec[size-1] = result.num_vec[size-1] & max_mask;
        return result;
    }
    //working
    BigInt operator >>(int n){
        BigInt result;
        result.num_vec = num_vec;
        int size = result.num_vec.size();
        long long int mask = (one << n)-1;

        //add a 0 untill n is less than max pow
        while(n > max_pow){
            result.num_vec.pop_back();
            n -= max_pow;
        }
        //shift each number by n and add overflow from number to the left
        for(int i=0; i <size-1; i++){
            cout << "i" << i << endl;
            result.num_vec[size-1-i] = result.num_vec[size-1-i] >> n;
            result.num_vec[size-1-i] += (result.num_vec[size-2-i] & mask) << (max_pow - n);
        }
        result.num_vec[0] = result.num_vec[0] >> n;
        return result;
    }
    void operator +=(BigInt b){
        if(b.negative && !this->negative){
            if(b>*this){
                this->negative = true;
            }
            *this -= b;
            return;
        }else if(!b.negative && this->negative){
            if(b>*this){
                this->negative = false;
                b -= *this;
                *this = b;
            }
            *this -= b;
            return;
        }
        int b_size = b.num_vec.size();
        int size = num_vec.size();
        if(size <= b_size){
            int difference = b_size - size;
            for(int i=0; i<=difference; i++){
                num_vec.push_front(0);
            }
            size += (difference + 1);
        }
        unsigned long long int carry = 0;
        for(int i=0; i < b_size; i++){
            // /cout << i << endl;
            num_vec[size-1-i] += b.num_vec[b_size-1-i] + carry;
            if(num_vec[size-1-i] > max_int){
                //carry = num_vec[size-1-i] << max_pow;
                carry = 1;
                num_vec[size-1-i] -= max_int;
            }
        }
        if(carry){
            num_vec[0] = carry;
        }
        this->flatten();
    }
    //working
    void operator -=(BigInt b){
        if((b.negative && !this->negative) || (!b.negative && this->negative)){
            *this += b;
        }
        if(!b.negative && !this->negative){
            if(b > *this){
                cout << "stuff" <<endl << "b";
                b.print();
                this->print();
                b -= *this;
                *this = b;
                this->negative = true;
            }
        }else if(b.negative && this->negative){
            if(b > *this){
                b.negative = false;
                this->negative = false;
                b -= *this;
                *this = b;
                return;
            }
            b.negative = false;
            this->negative = false;
            *this -= b;
            this->negative = true;
            return;
        }
        int b_size = b.num_vec.size();
        int size = num_vec.size();

        if(size <= b_size){
            int difference = b_size - size;
            for(int i=0; i<=difference; i++){
                num_vec.push_front(0);
            }
            size += (difference + 1);
        }
        unsigned long long int carry = 0;
        for(int i=0; i < b_size; i++){
            if(num_vec[size-1-i] < (b.num_vec[b_size-1-i] + carry)){
                num_vec[size-1-i] += max_int;
                carry = 1;
            }
            num_vec[size-1-i] -= (b.num_vec[b_size-1-i] + carry);
        }
        this->flatten();
    }
    void operator -=(int b){
        BigInt c({(unsigned long long)b});
        BigInt d = *this;
        d -= c;
        num_vec = d.num_vec;
        negative = d.negative;
    }
    void operator +=(int b){
        BigInt c({(unsigned long long)b});
        BigInt d = *this;
        d += c;
        num_vec = d.num_vec;
        negative = d.negative;
    }
    BigInt operator *(BigInt b){
        vector<BigInt> pows;
        BigInt result;
        int size = num_vec.size();
        int b_size = b.num_vec.size();
        for(int i=0; i <b_size; i++){
            for(int j=0; j<num_vec.size(); j++){
                BigInt mult;
                mult.num_vec.push_back(b.num_vec[b_size-1-i] * num_vec[size-1-j]);
                if(mult.num_vec[0] > max_int){
                    //put the bits greater than 32 in a new entry
                    mult.num_vec.push_front(mult.num_vec[0] >> 32);
                    //use a bit mask to remove bits greater than 32 from original entry
                    mult.num_vec[0] = mult.num_vec[0] & (max_int - 1);
                }
                for(int n=0; n < (i+j); n++){
                    mult.num_vec.push_back(0);
                }
                pows.push_back(mult);
            }
        }
        for(int i=0; i < pows.size(); i++){
            result += pows[i];
        }
        return result;
    }
    BigInt operator /(BigInt b){
        BigInt result;
        


        return result;
    }
    //working
    bool operator >(BigInt b){
        if(negative && !b.negative){return false;}
        if(!negative && b.negative){return true;}
        bool response = (!negative && !b.negative);
        this->flatten();
        b.flatten();
        int size = num_vec.size();
        int b_size = b.num_vec.size();
        if(size != b_size){return size > b_size;}
        for(int i = 0; i < size; i++){
            if(num_vec[i] > b.num_vec[i]){
                return response;
            }
        }
        return !response;
    }
    void operator =(BigInt b){
        this->num_vec = b.num_vec;
    }
    bool operator ==(int b){
        this->flatten();
        if(num_vec.size() != 1){return false;}
        return num_vec[0] == b;
    }
    bool operator ==(BigInt b){
        b.flatten();
        this->flatten();
        if(b.num_vec.size() != num_vec.size()){return false;}
        for(int i = 0; i < num_vec.size(); i++){
            if(num_vec[i]!= b.num_vec[i]){return false;}
        }
        return true;
    }

    BigInt operator %(BigInt b){
        BigInt temp;
        int max_bit = this->max_bit();
        //cout << max_bit << endl;
        int b_max_bit = b.max_bit();
        //cout << b_max_bit << endl;
        this->flatten();
        b.flatten();
        BigInt result = *this;
        while(result > b){
            //result.print();
            temp = (b << (max_bit - b_max_bit -1));
            //temp.print();
            while(result > temp){
                result -= temp;
                //result.print();
            }
            max_bit = result.max_bit();
        }
        return result;
    }
    BigInt modulo_pow(BigInt b, BigInt c){
        //cout << "hell0" << endl;
        BigInt prev;
        int max = b.max_bit();
        BigInt result;
        result.num_vec = {1};
        int size = b.num_vec.size();

        //auto start = chrono::steady_clock::now();
        for(int i=0; i<=max; i++){
            if(i == 0){
                prev = *this % c;
            }else{
                prev = (prev*prev);
                prev = prev % c;
            }
            if(b.num_vec[size-1-i]){
                result = result * prev;
            }
        }
        //auto end = chrono::steady_clock::now();
        // cout << "Forloop Time : "
        //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
        //     <<" ns" <<endl;

        result = result % c;
        result.flatten();
        
        return result;
    }

};