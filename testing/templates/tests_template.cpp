#include <vector>
#include <cmath>
#include <iostream>
//#include "bigint.hpp"
#include "../../bigint.hpp"
#include <chrono>
using namespace std;

{% for testKey in test_cases.keys() %}
void {{testKey}}(int &passed, int &failed){
    {% for testCaseKey in test_cases[testKey] %}
    //{{testCaseKey}}
    {
        BigInt a({{test_cases[testKey][testCaseKey][0]}});
        BigInt b({{test_cases[testKey][testCaseKey][1]}});
        BigInt c;
        BigInt d({{test_cases[testKey][testCaseKey][2]}});
        {% if test_cases[testKey][testCaseKey]|length == 4 %}
        BigInt e({{test_cases[testKey][testCaseKey][3]}});
        {% endif %}
        {% if test_cases[testKey][testCaseKey]|length == 5 %}
        BigInt e({{test_cases[testKey][testCaseKey][3]}});
        int f = {{test_cases[testKey][testCaseKey][4]}};
        {% endif %}
        {{operands[testKey][0]}};
        bool success = {{operands[testKey][1]}};
        cout << (success ? "\033[32m":"\033[31m") << "{{testKey}} {{testCaseKey}} " << (success ? "Pass":"Fail") << "\033[0m" << endl;
        if(!success){
            failed++;
            a.print(); 
            b.print(); 
            c.print(); 
            d.print();
            {% if test_cases[testKey][testCaseKey]|length == 4 %}
            e.print();
            {% endif %}
            {% if test_cases[testKey][testCaseKey]|length == 5 %}
            e.print();
            cout << f << endl;
            {% endif %}
        }else{
            passed++;
        }
    } 
    {% endfor %}
}
{% endfor %}


int main(){
    int passed = 0;
    int failed = 0;
{% for testKey in test_cases.keys() %}
    {{testKey}}(passed,failed);
    cout << endl;
{% endfor %}
    cout << "Passed " << passed << endl;
    cout << "Failed " << failed << endl;
}