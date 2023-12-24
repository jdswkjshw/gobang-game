#include <iostream>
#include <string>
#include "password.h"
using namespace std;


int main() {
    // 定义一个UserData对象，存储用户输入的username和password
    UserData data;
    // 提示用户输入username
    cout << "请输入username: ";
    // 从标准输入读取username
    cin >> data.username;
    // 提示用户输入password
    cout << "请输入password: ";
    // 从标准输入读取password
    cin >> data.password;
    // 创建一个Password对象，传入UserData对象
    Password p(data);
    string a = p.encrypt(data.password, data.username);
    cout << a;

    cout<<p.decrypt(a, data.username);
    return 0;
}
