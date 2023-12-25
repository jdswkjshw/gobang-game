#include <iostream>
#include <string>
#include"password.h"
using namespace std;

Password::Password(UserData d) :data(d) {}

bool Password::judgestring(string s) {
    for (char c : s) {
        if (!isalnum(c)) {
            return false;
        }
    }
    if (data.username.length() > 20 || data.password.length() > 20) 
        return false;
    return true;
}

int Password::charToInt(char c) {
    // 字符是大写字母，将其转换为0-25的整数
    if (isupper(c)) {
        int x = c - 'A';
        return x;
    }
    // 字符是小写字母，将其转换为26-51的整数
    else if (islower(c)) {
        int x = c - 'a' + 26;
        return x;
    }
    // 字符是数字，将其转换为52-61的整数
    else if (isdigit(c)) {
        int x = c - '0' + 52;
        return x;
    }
    // 表示字符无效
    else {
        return -1;
    }
}

char Password::intToChar(int x) {
    // 0-25，将其转换为A-Z的字符
    if (x >= 0 && x <= 25) {
        char c = x + 'A';
        return c;
    }
    // 26-51，将其转换为a-z的字符
    else if (x >= 26 && x <= 51) {
        char c = x - 26 + 'a';
        return c;
    }
    // 52-61，将其转换为0-9的字符
    else if (x >= 52 && x <= 61) {
        char c = x - 52 + '0';
        return c;
    }
    else {
        return '?';
    }
}

char Password::encrypt(char c, char key) {
    int x = charToInt(c);
    int y = charToInt(key);

    int z = (x + y) % 62; // 使用维吉尼亚加密
    char e = intToChar(z); // 将加密后的整数转换为字符
    return e;
}

string Password::encrypt(string s, string key) {
    string result = "";
    int n = s.length();
    int m = key.length();
    // 遍历字符串中的每个字符
    for (int i = 0; i < n; i++) {
        // 使用循环的方式，获取对应的key字符
        char k = key[i % m];
        // 加密当前字符
        char e = encrypt(s[i], k);
        result += e;
    }
    return result;
}

char Password::decrypt(char c, char key) {
    int x = charToInt(c);
    int y = charToInt(key);

    int z = (x - y + 62) % 62; // 使用维吉尼亚解密公式
    char d = intToChar(z); // 将解密后的整数转换为字符
    return d;
}

string Password::decrypt(string s, string key) {
    string result = "";
    int n = s.length();
    int m = key.length();
    // 遍历字符串中的每个字符
    for (int i = 0; i < n; i++) {
        // 使用循环的方式，获取对应的key字符
        char k = key[i % m];
        // 使用解密函数，解密当前字符
        char d = decrypt(s[i], k);
        result += d;
    }
    return result;
}