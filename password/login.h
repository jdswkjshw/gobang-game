#pragma once
#include <iostream>
#include <string>
#include"password.h"
#include"register.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;

// login�� �̳�register�� ��ʵ��У���û������빦��
class Login :public Register {
private:
	string inname="";
	string inpassword = "";
	//fstream file;
public:
	Login(UserData d);
	// �Ӽ��������ȡinname inpassword
	bool getinfo();
	
	// �򿪲���ȡ�ļ�
	// У���û���������
	int checkuser();
};
