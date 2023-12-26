#include <iostream>
#include <string>
#include<fstream>
#include<vector>
#include <sstream>
#include<io.h>
#include<graphics.h>
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
	else {
		MessageBox(
			NULL,
			(LPCWSTR)L"用户名或密码不能为空！",
			(LPCWSTR)L"登录界面",
			MB_ICONWARNING | MB_OK
		);
		return false;
	}

}

bool Login::checkuser()
{
	// 用户不存在
	if (!openFile(inname)) {
		MessageBox(
			NULL,
			(LPCWSTR)L"找不到用户！",
			(LPCWSTR)L"登录界面",
			MB_ICONWARNING | MB_OK
		);
		return false;
	}
	else {
		readData();
		// 密码错误
		if (data.password != inpassword) {
			MessageBox(
				NULL,
				(LPCWSTR)L"密码错误！",
				(LPCWSTR)L"登录界面",
				MB_ICONWARNING | MB_OK
			);
			return false;
		}
		else {
			MessageBox(
				NULL,
				(LPCWSTR)L"登录成功！请使用！",
				(LPCWSTR)L"登录界面",
				MB_ICONINFORMATION | MB_OK
			);
			return true;
		}
	}
}

