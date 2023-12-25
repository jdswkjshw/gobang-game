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
    // �ַ��Ǵ�д��ĸ������ת��Ϊ0-25������
    if (isupper(c)) {
        int x = c - 'A';
        return x;
    }
    // �ַ���Сд��ĸ������ת��Ϊ26-51������
    else if (islower(c)) {
        int x = c - 'a' + 26;
        return x;
    }
    // �ַ������֣�����ת��Ϊ52-61������
    else if (isdigit(c)) {
        int x = c - '0' + 52;
        return x;
    }
    // ��ʾ�ַ���Ч
    else {
        return -1;
    }
}

char Password::intToChar(int x) {
    // 0-25������ת��ΪA-Z���ַ�
    if (x >= 0 && x <= 25) {
        char c = x + 'A';
        return c;
    }
    // 26-51������ת��Ϊa-z���ַ�
    else if (x >= 26 && x <= 51) {
        char c = x - 26 + 'a';
        return c;
    }
    // 52-61������ת��Ϊ0-9���ַ�
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

    int z = (x + y) % 62; // ʹ��ά�����Ǽ���
    char e = intToChar(z); // �����ܺ������ת��Ϊ�ַ�
    return e;
}

string Password::encrypt(string s, string key) {
    string result = "";
    int n = s.length();
    int m = key.length();
    // �����ַ����е�ÿ���ַ�
    for (int i = 0; i < n; i++) {
        // ʹ��ѭ���ķ�ʽ����ȡ��Ӧ��key�ַ�
        char k = key[i % m];
        // ���ܵ�ǰ�ַ�
        char e = encrypt(s[i], k);
        result += e;
    }
    return result;
}

char Password::decrypt(char c, char key) {
    int x = charToInt(c);
    int y = charToInt(key);

    int z = (x - y + 62) % 62; // ʹ��ά�����ǽ��ܹ�ʽ
    char d = intToChar(z); // �����ܺ������ת��Ϊ�ַ�
    return d;
}

string Password::decrypt(string s, string key) {
    string result = "";
    int n = s.length();
    int m = key.length();
    // �����ַ����е�ÿ���ַ�
    for (int i = 0; i < n; i++) {
        // ʹ��ѭ���ķ�ʽ����ȡ��Ӧ��key�ַ�
        char k = key[i % m];
        // ʹ�ý��ܺ��������ܵ�ǰ�ַ�
        char d = decrypt(s[i], k);
        result += d;
    }
    return result;
}