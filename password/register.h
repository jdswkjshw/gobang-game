#pragma once
#include <iostream>
#include <string>
#include"password.h"
#include<fstream>
#include<vector>
#include <sstream>
#include<graphics.h>
#include<winuser.h>
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
    // ������Ӽ����û��Ƿ��Ѿ����ڹ���
    bool openFile(string username);
    // д��һ���ַ������ļ���
    bool writeLine(string s);
    // ��ȡһ���ַ������ļ���
    string readLine();
    // ��UserData���������д�뵽�ļ���
    // ����Ҫ��������ݣ������ı�����е�ֵ
    bool writeData(); // ע���¼ʱʹ��
    bool writeData_close(); //����ر�ʱ����ʤ��ʧ������Ϣ
    // ���ļ��е����ݽ��ܲ���ȡ��UserData������
    bool readData();
    // ����UserData����ĵ�¼ʱ�䣬��д�뵽�ļ���
    bool updateLoginTime(); // ע���¼ʱʹ��
    bool writeLoginTime(); // ����ر�ʱд�����е�¼ʱ��
    // �������� ע���Ƿ�ɹ�
    void showSuccess(bool b)
    {
        // ���д�����ݳɹ�
        if (b)
        {
            int msgboxID = MessageBox(
                NULL,
                (LPCWSTR)L"ע��ɹ���",
                (LPCWSTR)L"ע����Ϣ",
                MB_ICONINFORMATION | MB_OK
            );

        }
        else {
            MessageBox(
                NULL,
                (LPCWSTR)L"ע��ʧ�ܣ������ԣ�",
                (LPCWSTR)L"ע����Ϣ",
                MB_ICONWARNING | MB_OK
            );
        }
    }

};