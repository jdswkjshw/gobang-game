#include <iostream>
#include <string>
#include"password.h"
#include"register.h"
#include"login.h"
#include<fstream>
#include<vector>
#include <sstream>
using namespace std;


int main() {
    // ����һ��UserData���󣬴洢�û������username��password
   UserData data ;
    // ��ʾ�û�����username
    cout << "������username: ";
    // �ӱ�׼�����ȡusername
    cin >> data.username;
    // ��ʾ�û�����password
    cout << "������password: ";
    // �ӱ�׼�����ȡpassword
    cin >> data.password;
 //   // ����һ��Password���󣬴���UserData����
 //   /*Register p(data);*/
 //   //string t=p.encrypt(data.password, data.username);
 //   //cout << t << endl;
 //   //data.password = t;
 //   //cout << p.decrypt(data.password, data.username);
 //   Register a(data);
 ////   //a.data.password = p.encrypt(data.password, data.username);
 ////   //cout << a.data.password << endl;
 //   a.openFile(data.username);
 //   //a.data.wins = "0";
 //   a.readData();
 //   a.data.losses = "1";
 //   a.writeData();
 //   a.closeFile();
 //   Register b(data);
 //   b.openFile();
 //   b.readData();
 //   a.readData();
 //   //a.data.wins = "1";
 //   //a.data.losses = "0";
 // 
 ///*   a.data.wins = a.encrypt(a.data.wins, a.data.username);
 //   a.data.losses = a.encrypt(a.data.losses, a.data.username);*/
 //   cout << a.data.wins << endl;
 //   cout << a.data.losses;
 //   a.writeData();
 //   //a.updateLoginTime();
 //   a.closeFile();
    //Register b(data);
    //b.openFile("123");
    //b.readData();
    //cout << b.data.wins;
    Login g(data);
    g.getinfo();
    //cout<<g.getinfo()<<endl;
    cout<<g.checkuser();
    return 0;
}
