#include <iostream>
#include <string>
#include "password.h"
using namespace std;


int main() {
    // ����һ��UserData���󣬴洢�û������username��password
    UserData data;
    // ��ʾ�û�����username
    cout << "������username: ";
    // �ӱ�׼�����ȡusername
    cin >> data.username;
    // ��ʾ�û�����password
    cout << "������password: ";
    // �ӱ�׼�����ȡpassword
    cin >> data.password;
    // ����һ��Password���󣬴���UserData����
    Password p(data);
    string a = p.encrypt(data.password, data.username);
    cout << a;

    cout<<p.decrypt(a, data.username);
    return 0;
}
