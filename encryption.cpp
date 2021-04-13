#include <Python.h>
#include <vector>
#include <cmath>
#include "bigint.hpp"
#include "rsa.cpp"

std::string primeString(int n){
    BigInt a;
    a.random(n);
    if(a.even()){
        a.addition_self_unsigned(1);
    }
    int count = 1;
    while(!a.is_prime(10)){
        count ++;
        a.random(n);
        if(a.even()){
            a.addition_self_unsigned(1);
        }
        std::cout << "Attempts " << count << std::endl;
    }
    return a.toString();
}


static PyObject* generatePrime(PyObject* self, PyObject* args){
    int n;
    if (!PyArg_ParseTuple(args,"i",&n)){return NULL;}
    std::string result = primeString(n).c_str();
    std::vector<char> writable(result.begin(), result.end());
    writable.push_back('\0');
    return PyLong_FromString(&*writable.begin(),NULL  ,10);

} 

// static PyObject* encryptNum(PyObject* self, PyObject* args){
//     std::string message;
//     std::string key;
//     std::string modulus;
//     if (!PyArg_ParseTuple(args,"s",&message)){return NULL;}
//     if (!PyArg_ParseTuple(args,"s",&key)){return NULL;}
//     if (!PyArg_ParseTuple(args,"s",&modulus)){return NULL;}
//     BigInt messageInt(message);
//     BigInt keyInt(key);
//     BigInt modulusInt(modulus);
//     BigInt resultInt = encrypt(messageInt,keyInt,modulusInt)
//     std::string result = result.toString();
//     std::vector<char> writable(result.begin(), result.end());
//     writable.push_back('\0');
//     return PyLong_FromString(&*writable.begin(),NULL  ,10);

// } 

static PyMethodDef mainMethods[] = {
 {"generatePrime",generatePrime,METH_VARARGS,"Generate a prime number number with n bits"},
 {NULL,NULL,0,NULL}
};

static PyModuleDef encryption = {
 PyModuleDef_HEAD_INIT,
 "encryption","Prime Number Generation",
 -1,
 mainMethods
};

PyMODINIT_FUNC PyInit_encryption(void){
 return PyModule_Create(&encryption);
}