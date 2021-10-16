#include <iostream>
using namespace std;

void test(unsigned int x){
    unsigned int b = 4;
    b += x;
    cout << b;
}

int main(){
    int x = -1;
    test(x);
}