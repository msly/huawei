#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;

int getCheckNum(string code) {
    int sum = 0;
    for (size_t i=0; i<code.size(); ++i) {
        if (i % 2 == 0) {
            sum += (code[i] - '0');
        } else {
            int even = (code[i] - '0') * 2;
            if (even >= 10) {
                sum += 1;
            }
            sum += (even % 10);
        }
    }

    return (10 - sum % 10) % 10;
}

int main() {

    cout << "请输入基础数字： 如86762802603" << endl;
    string base;
    cin >> base;

    cout << "请输入生成个数" << endl;
    int count;
    cin >> count;

    // 计算填0个数
    int num0 = 14 - base.size();

    stringstream os;
    for (int i=0; i<count; ++i) {
        os.str("");
        os << base << setw(num0) << setfill('0') << i;

        cout << os.str() << getCheckNum(os.str()) << endl;
    }

    cin >> count;
    return 0;
}
