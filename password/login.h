#pragma once
#include <iostream>
#include <string>
#include"password.h"
#include"register.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;

// login类 继承register类 并实现校验用户名密码功能
class Login :public Register {
private:
	string inname="";
	string inpassword = "";
	//fstream file;
public:
	Login(UserData d);
	// 从键盘输入获取inname inpassword
	bool getinfo();
	
	// 打开并读取文件
	// 校验用户名和密码
	int checkuser();
};
