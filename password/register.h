#pragma once
#include <iostream>
#include <string>
#include"password.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;

// Register�� ʵ���ļ��Ĵ����Ͷ�д
// ��Ҫ��ӵ���ע��ɹ����ڹ���
// ��Ҫ��ӵ������û��ѱ�ע�ᴰ�ڹ���
// �ļ����� data.username
// �ļ����� 
// ��һ�� �û��� ���Ĵ洢
// �ڶ��� ���� ���û�������
// ������ ʤ���� ���������
// ������ ʧ���� ���������
// ֮�� ���μ�¼��¼ʱ��
class Register : public Password {
private:
    fstream file;

public:
    Register(UserData d);
    // �����������ر��ļ���ָ��
    ~Register();
    // �������һ���ļ����ļ���Ϊdata.username
    bool openFile();
    bool closeFile();
    bool openFile(string username);
    // д��һ���ַ������ļ���
    bool writeLine(string s);
    // ��ȡһ���ַ������ļ���
    string readLine();
    // ��UserData���������д�뵽�ļ���
    // ����Ҫ��������ݣ������ı�����е�ֵ
    bool writeData();
    // ���ļ��е����ݽ��ܲ���ȡ��UserData������
    bool readData();
    // ����UserData����ĵ�¼ʱ�䣬��д�뵽�ļ���
    bool updateLoginTime();
};