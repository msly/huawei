#include <iostream>
#include <string>
#include <sstream>
#include "md5.h"

using namespace std;

int main(){

    string model;
    string imei;

    cout << "input model : (such as:HUAWEI Y300-0000)" << endl;
    getline(cin, model);

    cout << "input imei:" << endl;
    cin >> imei;


    // md5
    string hash = md5(model + imei);

    // first8 xor last8
    string hash0 = hash.substr(0, 8);
    string hash8 = hash.substr(hash.size() - 8, 8);

    char *str;
    long long iHash3 = strtoll(hash0.c_str(), &str, 16);
    long long iHash8 = strtoll(hash8.c_str(), &str, 16);

    long long ret = iHash3 ^ iHash8;
    stringstream os;
    os << hex << ret;

    // first 8
    string first8 = os.str().substr(0, 8);


    os.str("");
    for (size_t i = 0; i < first8.size(); ++i){
        if (first8[i] > 'a'){
            os << char(first8[i] - 0x31);
        }else {
            os << first8[i];
        }
    }

    // deal 0
    string result = os.str();
    while (result[0] == '0'){
        result = result.substr(1, result.size() - 1) + '0';
    }

    cout << "------------------------------" << endl;
    cout << "MODEL:" << model << endl;
    cout << "IEMI:" << imei << endl;
    cout << "Product ID:" << result << endl;

    cin >> imei;
    return 0;
}
