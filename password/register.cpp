#include <iostream>
#include <string>
#include"password.h"
#include"register.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;




Register::Register(UserData d) : Password(d) {
}

Register::~Register() {
    // ����ļ��������Ѿ��򿪣��ر��ļ�������
    if (file.is_open()) {
        file.close();
    }
}

// ���������ⲿ��ʵ��openFile����
bool Register::openFile() {
    // ��ȡ�ļ���
    string filename = data.username;
    // �Զ�дģʽ��һ���ļ�������������򴴽�
    file.open(filename, ios::in | ios::out);
    // �ж��ļ��Ƿ�򿪳ɹ���������Ӧ�Ĳ���ֵ
    return file.is_open();
}

// ���������ⲿ��ʵ��writeLine����
bool Register::writeLine(string s) {
    // ����ļ��������Ѿ��򿪣����ļ���д��һ�����ݣ����ϻ��з�
    if (file.is_open()) {
        file << s << endl;
    }
    // �ж��ļ��Ƿ�д��ɹ���������Ӧ�Ĳ���ֵ
    return file.good();
}

// ���������ⲿ��ʵ��readLine����
string Register::readLine() {
    // ����һ���ַ������洢��ȡ�Ľ��
    string result = "";
    // ����ļ��������Ѿ��򿪣����ļ��ж�ȡһ������
    if (file.is_open()) {
        getline(file, result);
    }
    // ���ض�ȡ���ַ���
    return result;
}

// ���������ⲿ��ʵ��writeData����
bool Register::writeData() {
    // ����ļ��������Ѿ��򿪣��ر���
    if (file.is_open()) {
        file.close();
    }
    // �Զ�д�ͽض�ģʽ��һ���ļ�������������򴴽�
    file.open(data.username, ios::in | ios::out | ios::trunc);
    // ����ļ��������Ѿ��򿪣����ļ�ָ���ƶ����ļ��Ŀ�ͷ
    if (file.is_open()) {
        file.seekp(0, ios::beg);
        // д���û��������Ĵ洢
        bool b1 = writeLine(data.username);
        // д�����룬���û�������
        string encryptedPassword = encrypt(data.password, data.username);
        bool b2 = writeLine(encryptedPassword);
        // д��ʤ���������������
        string encryptedWins = "Wins " + encrypt(data.wins, data.password);
        bool b3 = writeLine(encryptedWins);
        // д��ʧ���������������
        string encryptedLosses = "Losses " + encrypt(data.losses, data.password);
        bool b4 = writeLine(encryptedLosses);
        // ������κ�һ��д��ʧ�ܣ�����false
        if (!b1 || !b2 || !b3 || !b4) {
            return false;
        }
        // ���ȫ��д��ɹ�������true
        return true;
    }
    // ����ļ�������û�д򿪣�����false
    return false;
}

// ���������ⲿ��ʵ��readData����
bool Register::readData() {
    // ����ļ��������Ѿ��򿪣����ļ�ָ���ƶ����ļ��Ŀ�ͷ
    if (file.is_open()) {
        file.seekg(0, ios::beg);
        // ��ȡ�û��������Ĵ洢
        string username = readLine();
        // ��ȡ���룬���û�������
        string encryptedPassword = readLine();
        string password = decrypt(encryptedPassword, username);
        // ��ȡʤ���������������
        string encryptedWins = readLine();
        string wins = decrypt(encryptedWins.substr(5), password); //subtr���� ��ȡ�����ַ���
        // ��ȡʧ���������������
        string encryptedLosses = readLine();
        string losses = decrypt(encryptedLosses.substr(7), password);
        // ��ȡ��¼ʱ�䣬���Ĵ洢���ϲ�����Ϊһ���ַ���
        string loginTime = "";
        string line = readLine();
        while (line != "") {
            loginTime += line + "\n";
            line = readLine();
        }
        // ������κ�һ����ȡʧ�ܣ�����false
        if (username == "" || password == "" || wins == "" || losses == "") {
            return false;
        }
        // ���ȫ����ȡ�ɹ�������ȡ�����ݸ�ֵ��UserData���󣬷���true
        data.username = username;
        data.password = password;
        data.wins = wins;
        data.losses = losses;
        data.loginTime = loginTime;
        return true;
    }
    // ����ļ�������û�д򿪣�����false
    return false;
}

// ���������ⲿ��ʵ��updateLoginTime����
bool Register::updateLoginTime() {
    // ����ļ��������Ѿ��򿪣���ȡ��ǰ��ϵͳʱ�䣬ת��Ϊ�ַ���
    if (file.is_open()) {
        time_t t = time(NULL);
        char buffer[20];
        strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
        string currentTime = string(buffer);
        // ����ǰʱ�丳ֵ��UserData����ĵ�¼ʱ��
        data.loginTime = currentTime;
        // ���ļ�ָ���ƶ����ļ���ĩβ
        file.seekp(0, ios::end);
        // ���UserData����ĵ�¼ʱ��Ϊ�գ�ֱ��д�뵱ǰʱ��
        if (data.loginTime == "") {
            bool b = writeLine(currentTime);
            // ���д��ʧ�ܣ�����false
            if (!b) {
                return false;
            }
        }
        // ���UserData����ĵ�¼ʱ�䲻Ϊ�գ�������д���¼ʱ���е�ÿһ������д�뵱ǰʱ��
        else {
            // ����¼ʱ��ָ�Ϊ����ַ����������з��ָ�
            vector<string> times;
            // ����һ���յ�stringstream����
            stringstream ss;
            // ��stringstream��������data.loginTime�ַ���
            ss << data.loginTime;
            string line;
            while (getline(ss, line, '\n')) {
                times.push_back(line);
            }
            // ����ÿ���ַ�����д�뵽�ļ���
            for (string time : times) {
                bool b = writeLine(time);
                // ���д��ʧ�ܣ�����false
                if (!b) {
                    return false;
                }
            }
            // д�뵱ǰʱ��
            bool b = writeLine(currentTime);
            // ���д��ʧ�ܣ�����false
            if (!b) {
                return false;
            }
        }
        // ���д��ɹ�������true
        return true;
    }
    // ����ļ�������û�д򿪣�����false
    return false;
}

