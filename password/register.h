#pragma once
#include <iostream>
#include <string>
#include"password.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;

// Register类 实现文件的创建和读写
// 需要添加弹出注册成功窗口功能
// 需要添加弹出该用户已被注册窗口功能
// 文件名称 data.username
// 文件内容 
// 第一行 用户名 明文存储
// 第二行 密码 用用户名加密
// 第三行 胜利数 用密码加密
// 第四行 失败数 用密码加密
// 之后 依次记录登录时间
class Register : public Password {
private:
    fstream file;

public:
    Register(UserData d);
    // 析构函数，关闭文件的指针
    ~Register();
    // 创建或打开一个文件，文件名为data.username
    bool openFile();
    bool closeFile();
    bool openFile(string username);
    // 写入一行字符串到文件中
    bool writeLine(string s);
    // 读取一行字符串从文件中
    string readLine();
    // 将UserData对象的数据写入到文件中
    // 按照要求加密数据，但不改变对象中的值
    bool writeData();
    // 将文件中的数据解密并读取到UserData对象中
    bool readData();
    // 更新UserData对象的登录时间，并写入到文件中
    bool updateLoginTime();
};