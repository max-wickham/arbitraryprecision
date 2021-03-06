#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <deque>
#include <chrono>
#include <chrono>
using namespace std;

class BigInt {
    //private:
    static const long long one = 1;
    static const int max_pow = 32;
    static const long long int max_int = (one << max_pow);
    static const long long int max_mask = (one << max_pow) -1;
    deque<unsigned long long int> num_vec = {0};
    bool negative = false;

    public:
    BigInt(){}
    BigInt (vector<unsigned long long int> _num_vec){
        for(auto x: _num_vec){
            num_vec.push_back(x);
        }
    }
    
    void rand(int n, std::chrono::_V2::steady_clock::time_point start){
        num_vec = {};
        //std::default_random_engine generator;
        std::uniform_int_distribution<unsigned long long int> distribution(1,pow(2,32)-1);
        auto end = chrono::steady_clock::now();
        int t = (int) chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        std::default_random_engine generator(t);
        while(n > max_pow){
            unsigned long long num;
            num = distribution(generator);
            num_vec.push_back(num);
            n -= max_pow;
        }
        if(n){
            //cout << n << endl;
            //cout << pow(2,n)-1 << endl;
            std::default_random_engine generator2;
            unsigned long long x = pow(2,n)-1;
            std::uniform_int_distribution<unsigned long int> distribution2(x/2+1,x);
            unsigned long long num;
            num = distribution2(generator);
            //cout << num << endl;
            num_vec.push_front((unsigned long long int)num);
        }
        //if(num_vec[num_vec.size()-1] % 2 ==0){
        if(!(num_vec[num_vec.size()-1]&1)){
            num_vec[num_vec.size()-1] += 1;
        }
    }
    void rand(BigInt n, std::chrono::_V2::steady_clock::time_point start){
       //cout << "end";
        num_vec = {};
        auto end = chrono::steady_clock::now();
        int t = (int) chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        std::default_random_engine generator(t);
        std::uniform_int_distribution<unsigned long long int> distribution(1,pow(2,32)-1);
        int count = n.num_vec.size();
        while(count){
            unsigned long long num;
            num = distribution(generator);
            num_vec.push_back(num);
            count--;
        }
        std::uniform_int_distribution<unsigned long long int> distribution2(1,n.num_vec[0]);
        unsigned long long num;
        num = distribution(generator);
        num_vec.push_front(num);
        
    }
    void flatten(){
        while(!num_vec[0] && num_vec.size() > 1){
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
        //num_vec[0] = num_vec[0] & max_mask;
        unsigned long long int bits = num_vec[0];
        //int n = max_pow;
        //while(!(bits & (one << (n -1) ) ) ){
        //   n -= 1;
        //}
        int n = 0;
        while(bits){
            n += 1;
            bits = bits >> 1;
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
        int extra = 0;
        if(result.num_vec[0] >= pow(2,max_pow-n)){
            result.num_vec.push_front(result.num_vec[0] >> (max_pow-n));
            extra = 1;
            size += 1;
        }
        //shift each number by n and add overflow bits from number to the right
        for(int i=extra; i <size-1; i++){
            result.num_vec[i] = result.num_vec[i] << n;
            //result.num_vec[i] += result.num_vec[i+1] & mask;
            //cout << "i" << i << " " << ((result.num_vec[i+1] & reverse_mask) >> (max_pow -n)) << endl;
            //cout << "reverse " << reverse_mask <<endl;
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
            //cout << "i" << i << endl;
            result.num_vec[size-1-i] = result.num_vec[size-1-i] >> n;
            result.num_vec[size-1-i] += (result.num_vec[size-2-i] & mask) << (max_pow - n);
        }
        result.num_vec[0] = result.num_vec[0] >> n;
        return result;
    }
    void operator +=(BigInt &b){
        if(b.negative){
            if(!this->negative){
                this->negative = b>*this;
                *this -= b;
                return;
            }
        }else if (this->negative){
            if(b>*this){
                this->negative = false;
                BigInt c;
                c = b;
                c -= *this;
                //b -= *this;
                *this = c;
                return;
            }
            *this -= b;
            return;
        }
        //if(b.negative && !this->negative){
        //    if(b>*this){
        //        this->negative = true;
        //    }
         //   *this -= b;
        //    return;
        // }else if(!b.negative && this->negative){
        //     if(b>*this){
        //         this->negative = false;
        //         b -= *this;
        //         *this = b;
        //     }
        //     *this -= b;
        //     return;
        // }
        int b_size = b.num_vec.size();
        int size = num_vec.size();
        if(size <= b_size){
            //int difference = b_size - size;
            //for(int i=0; i<=difference; i++){
            //    num_vec.push_front(0);
            //}
            auto it = num_vec.end();
            num_vec.insert(it,0,b_size - size+1);
            size = b_size + 1;

        }
        bool carry = 0;
        int index = size-1;
        for(int i=0; i < b_size; i++){
            // /cout << i << endl;
            num_vec[index] += b.num_vec[b_size-1-i] + carry;
            if(num_vec[index] > max_int){
                //carry = num_vec[size-1-i] << max_pow;
                carry = 1;
                num_vec[index] -= max_int;
            }
            else{carry = 0;}
            index --;
        }
        while(carry){
            num_vec[index] += carry;
            if(num_vec[index] > max_int){
                //carry = num_vec[size-1-i] << max_pow;
                carry = 1;
                num_vec[index] = 0;
            }
            else{carry = 0;}
            index --;
        }
        this->flatten();
        // if(num_vec[0] == 0){
        //     num_vec.pop_front();
        // }
    }
    //working
    void operator -=(BigInt b){
        if((b.negative && !this->negative) || (!b.negative && this->negative)){
            *this += b;
        }
        if(!b.negative && !this->negative){
            if(b > *this){
                //cout << "stuff" <<endl << "b";
                //b.print();
                this->print();
                b -= *this;
                *this = b;
                this->negative = true;
                return;
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

        if(size > b_size){
            int difference = size - b_size;
            for(int i=0; i<difference; i++){
                b.num_vec.push_front(0);
            }
            b_size += (difference);
        }
        unsigned long long int carry = 0;
        for(int i=0; i < b_size; i++){
            if(num_vec[size-1-i] < (b.num_vec[b_size-1-i] + carry)){
                num_vec[size-1-i] += max_int;
                num_vec[size-1-i] -= (b.num_vec[b_size-1-i] + carry);
                carry = 1;
            }else{
                num_vec[size-1-i] -= (b.num_vec[b_size-1-i] + carry);
                carry = 0;
            }   
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
    BigInt operator *(BigInt &b){
        vector<BigInt> pows;
        BigInt result;
        int size = num_vec.size();
        int b_size = b.num_vec.size();
        BigInt mult;
        for(int i=0; i<b_size; i++){
            for(int j=0; j<size; j++){
                mult.num_vec.clear();
                mult.num_vec.push_back(b.num_vec[b_size-1-i] * num_vec[size-1-j]);
                //mult.flatten();
                if(mult.num_vec[0] > max_int){
                    //put the bits greater than 32 in a new entry
                    mult.num_vec.push_front(mult.num_vec[0] >> max_pow);
                    //use a bit mask to remove bits greater than 32 from original entry
                    mult.num_vec[1] = mult.num_vec[1] & max_mask;
                }
                //for(int n=0; n < (i+j); n++){
                //    mult.num_vec.push_back(0);
                //}
                auto it = mult.num_vec.end();
                mult.num_vec.insert(it,0,i+j);
                result += mult;
                //pows.push_back(mult);
            }
        }
        //for(int i=0; i < pows.size(); i++){
        //    result += pows[i];
        //}
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
            if(num_vec[i] != b.num_vec[i]){
                return !((num_vec[i] > b.num_vec[i]) ^ response);
            }
        }
        return !response;
    }
    bool operator <(BigInt b){
        this->flatten();
        b.flatten();
        if(b.num_vec.size() == num_vec.size()){
            for(int i = 0; i < num_vec.size(); i++){
                if(num_vec[i] != b.num_vec[i]){
                    return num_vec[i] < b.num_vec[i];
                }
            }
        }
        return b.num_vec.size() < num_vec.size();
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
            temp = b;
            if(max_bit - b_max_bit > 0){
                temp = (temp << (max_bit - b_max_bit - 1));
            }
            //temp = (b << (max_bit - b_max_bit));
            //temp.print();
            while(result > temp){
                result -= temp;
                //result.print();
            }
            max_bit = result.max_bit();
        }
        return result;
    }
    BigInt modulo_pow(BigInt e, BigInt m){
        // cout << "hell0" << endl;
        // BigInt prev;
        // int max = b.max_bit();
        // BigInt result;
        // result.num_vec = {1};
        // int size = b.num_vec.size();
        // cout << "hell0" << endl;
        // //auto start = chrono::steady_clock::now();
        // for(int i=0; i<=max; i++){
        //     cout << "i mod " << i << endl;
        //     if(i == 0){
        //         prev = *this % c;
        //     }else{
        //         prev = (prev*prev);
        //         prev = prev % c;
        //     }
        //     if(b.num_vec[size-1-(int)(i/max_pow)]){
        //         result = result * prev;
        //     }
        // }
        // //auto end = chrono::steady_clock::now();
        // // cout << "Forloop Time : "
        // //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
        // //     <<" ns" <<endl;

        // result = result % c;
        // result.flatten();
        
        // return result;
        BigInt result({1});
        BigInt b = *this;
        b = b % m;
        BigInt zero({0});
        while(e > zero){
            //if(e.num_vec[e.num_vec.size()-1]%2 == 1){
            if(e.num_vec[e.num_vec.size()-1]&1){    
                result = (result * b) % m;
            }
            e = e >> 1;
            b = (b * b) % m;
        }
        return result;
    }
    bool prime(int k = 6){
        auto start = chrono::steady_clock::now();
        BigInt n = *this;
        this->flatten();
        if(this->num_vec.size() == 1){
            if(this->num_vec[0] == 1){
                return false;
            }            
        }
        BigInt _n;
        _n = n;
        _n -= 1;
        BigInt s;
        BigInt r;
        r = n;
        //cout << "running";
        r -= 1;
        //auto start = chrono::steady_clock::now();
        while(r.even()){
            s += 1;
            r = r >> 1;
            //r.print();
        }
        // auto end = chrono::steady_clock::now();
        // cout << "Elapsed Time : "
        //     << chrono::duration_cast<chrono::nanoseconds>(end-start).count()
        //     <<" ns" <<endl;

        for(int i=0; i < k; i++){
            //cout << "i " << i <<  endl;
            //auto start = chrono::steady_clock::now();
            BigInt a;
            a.rand(_n,start);
            //auto end = chrono::steady_clock::now();
            BigInt x;
            x = a.modulo_pow(r,n);
            if(!(x == 1) && !(x == _n)){
                BigInt j;
                j += 1;
                while((j < s) && !(x == _n)){
                    x = x * x;
                    x = x % n;
                    if(x == 1){
                        return false;
                    } 
                    j += 1;
                }
                if(!(x==_n)){
                    return false;
                }
            }
        }
        return true;
    }
};