#include <iostream>
#include <string>
#include<fstream>
#include<vector>
#include <sstream>
#include"password.h"
#include"register.h"
#include"login.h"
using namespace std;

Login::Login(UserData d):Register(d)
{
}

bool Login::getinfo()
{
	cin >> inname >> inpassword;
	if (inname != "" && inpassword != "")
		return true;
	return false;
}

int Login::checkuser()
{
	// 用户不存在
	if (!openFile(inname))
		return 0;
	readData();
	// 密码错误
	if (data.password != inpassword)
		return 1;
	return 2;

}
