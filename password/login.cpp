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
			(LPCWSTR)L"�û��������벻��Ϊ�գ�",
			(LPCWSTR)L"��¼����",
			MB_ICONWARNING | MB_OK
		);
		return false;
	}

}

bool Login::checkuser()
{
	// �û�������
	if (!openFile(inname)) {
		MessageBox(
			NULL,
			(LPCWSTR)L"�Ҳ����û���",
			(LPCWSTR)L"��¼����",
			MB_ICONWARNING | MB_OK
		);
		return false;
	}
	else {
		readData();
		// �������
		if (data.password != inpassword) {
			MessageBox(
				NULL,
				(LPCWSTR)L"�������",
				(LPCWSTR)L"��¼����",
				MB_ICONWARNING | MB_OK
			);
			return false;
		}
		else {
			MessageBox(
				NULL,
				(LPCWSTR)L"��¼�ɹ�����ʹ�ã�",
				(LPCWSTR)L"��¼����",
				MB_ICONINFORMATION | MB_OK
			);
			return true;
		}
	}
}

