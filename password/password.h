#pragma once
#include <iostream>
#include <string>
using namespace std;

// user����
struct UserData {
    string username;
    string password;
    string wins;
    string losses;
    string loginTime;
};

// Password�� ʵ��ά�����Ǽ��ܽ��� ���username password�Ϸ���
// username password�Ϸ����������ֺ���ĸ��ɣ����Ȳ�����20
class Password {

public:
    UserData data = {0,0,"0","0",0};
    Password(UserData d);

    bool judgestring(string s); // ����ַ����Ƿ�ֻ������ĸ�����֣������Ƿ񲻳���20
    // ��һ���ַ�ת��Ϊһ��������A-Z��Ӧ0-25��a-z��Ӧ26-35��0-9��Ӧ52-61
    int charToInt(char c);
    // ������ת��Ϊ�ַ���0-25��ӦA-Z��26-51��Ӧa-z��52-61��Ӧ0-9
    char intToChar(int x);
    // ���ܽ��ܺ�������ı�data��Ա��ֵ
    char encrypt(char c, char key); // ʹ�ó˷������㷨����һ���ַ�  
    string encrypt(string s, string key); // ����һ���ַ���

    char decrypt(char c, char key); // ʹ�ó˷������㷨����һ���ַ�
    string decrypt(string s, string key); // ����һ���ַ���

};


