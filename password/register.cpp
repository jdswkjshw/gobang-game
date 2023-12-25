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
    // 如果文件流对象已经打开，关闭文件流对象
    if (file.is_open()) {
        file.close();
    }
}

// 在类声明外部，实现openFile方法
bool Register::openFile() {
    // 获取文件名
    string filename = data.username;
    // 以读写模式打开一个文件，如果不存在则创建
    file.open(filename, ios::in | ios::out);
    // 判断文件是否打开成功，返回相应的布尔值
    return file.is_open();
}

// 在类声明外部，实现writeLine方法
bool Register::writeLine(string s) {
    // 如果文件流对象已经打开，向文件中写入一行数据，加上换行符
    if (file.is_open()) {
        file << s << endl;
    }
    // 判断文件是否写入成功，返回相应的布尔值
    return file.good();
}

// 在类声明外部，实现readLine方法
string Register::readLine() {
    // 定义一个字符串，存储读取的结果
    string result = "";
    // 如果文件流对象已经打开，从文件中读取一行数据
    if (file.is_open()) {
        getline(file, result);
    }
    // 返回读取的字符串
    return result;
}

// 在类声明外部，实现writeData方法
bool Register::writeData() {
    // 如果文件流对象已经打开，关闭它
    if (file.is_open()) {
        file.close();
    }
    // 以读写和截断模式打开一个文件，如果不存在则创建
    file.open(data.username, ios::in | ios::out | ios::trunc);
    // 如果文件流对象已经打开，将文件指针移动到文件的开头
    if (file.is_open()) {
        file.seekp(0, ios::beg);
        // 写入用户名，明文存储
        bool b1 = writeLine(data.username);
        // 写入密码，用用户名加密
        string encryptedPassword = encrypt(data.password, data.username);
        bool b2 = writeLine(encryptedPassword);
        // 写入胜利数，用密码加密
        string encryptedWins = "Wins " + encrypt(data.wins, data.password);
        bool b3 = writeLine(encryptedWins);
        // 写入失败数，用密码加密
        string encryptedLosses = "Losses " + encrypt(data.losses, data.password);
        bool b4 = writeLine(encryptedLosses);
        // 如果有任何一步写入失败，返回false
        if (!b1 || !b2 || !b3 || !b4) {
            return false;
        }
        // 如果全部写入成功，返回true
        return true;
    }
    // 如果文件流对象没有打开，返回false
    return false;
}

// 在类声明外部，实现readData方法
bool Register::readData() {
    // 如果文件流对象已经打开，将文件指针移动到文件的开头
    if (file.is_open()) {
        file.seekg(0, ios::beg);
        // 读取用户名，明文存储
        string username = readLine();
        // 读取密码，用用户名解密
        string encryptedPassword = readLine();
        string password = decrypt(encryptedPassword, username);
        // 读取胜利数，用密码解密
        string encryptedWins = readLine();
        string wins = decrypt(encryptedWins.substr(5), password); //subtr函数 截取部分字符串
        // 读取失败数，用密码解密
        string encryptedLosses = readLine();
        string losses = decrypt(encryptedLosses.substr(7), password);
        // 读取登录时间，明文存储，合并多行为一个字符串
        string loginTime = "";
        string line = readLine();
        while (line != "") {
            loginTime += line + "\n";
            line = readLine();
        }
        // 如果有任何一步读取失败，返回false
        if (username == "" || password == "" || wins == "" || losses == "") {
            return false;
        }
        // 如果全部读取成功，将读取的数据赋值给UserData对象，返回true
        data.username = username;
        data.password = password;
        data.wins = wins;
        data.losses = losses;
        data.loginTime = loginTime;
        return true;
    }
    // 如果文件流对象没有打开，返回false
    return false;
}

// 在类声明外部，实现updateLoginTime方法
bool Register::updateLoginTime() {
    // 如果文件流对象已经打开，获取当前的系统时间，转换为字符串
    if (file.is_open()) {
        time_t t = time(NULL);
        char buffer[20];
        strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
        string currentTime = string(buffer);
        // 将当前时间赋值给UserData对象的登录时间
        data.loginTime = currentTime;
        // 将文件指针移动到文件的末尾
        file.seekp(0, ios::end);
        // 如果UserData对象的登录时间为空，直接写入当前时间
        if (data.loginTime == "") {
            bool b = writeLine(currentTime);
            // 如果写入失败，返回false
            if (!b) {
                return false;
            }
        }
        // 如果UserData对象的登录时间不为空，先依次写入登录时间中的每一条，再写入当前时间
        else {
            // 将登录时间分割为多个字符串，按换行符分割
            vector<string> times;
            // 创建一个空的stringstream对象
            stringstream ss;
            // 向stringstream对象输入data.loginTime字符串
            ss << data.loginTime;
            string line;
            while (getline(ss, line, '\n')) {
                times.push_back(line);
            }
            // 遍历每个字符串，写入到文件中
            for (string time : times) {
                bool b = writeLine(time);
                // 如果写入失败，返回false
                if (!b) {
                    return false;
                }
            }
            // 写入当前时间
            bool b = writeLine(currentTime);
            // 如果写入失败，返回false
            if (!b) {
                return false;
            }
        }
        // 如果写入成功，返回true
        return true;
    }
    // 如果文件流对象没有打开，返回false
    return false;
}

