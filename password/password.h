#pragma once
#include <iostream>
#include <string>
using namespace std;

// user数据
struct UserData {
    string username;
    string password;
    string wins;
    string losses;
    string loginTime;
};

// Password类 实现维多利亚加密解密 检查username password合法性
// username password合法：仅由数字和字母组成，长度不超过20
class Password {

public:
    UserData data = {0,0,"0","0",0};
    Password(UserData d);

    bool judgestring(string s); // 检查字符串是否只包含字母和数字，长度是否不超过20
    // 将一个字符转换为一个整数，A-Z对应0-25，a-z对应26-35，0-9对应52-61
    int charToInt(char c);
    // 将整数转换为字符，0-25对应A-Z，26-51对应a-z，52-61对应0-9
    char intToChar(int x);
    // 加密解密函数不会改变data成员的值
    char encrypt(char c, char key); // 使用乘法加密算法加密一个字符  
    string encrypt(string s, string key); // 加密一个字符串

    char decrypt(char c, char key); // 使用乘法解密算法解密一个字符
    string decrypt(string s, string key); // 解密一个字符串

};


