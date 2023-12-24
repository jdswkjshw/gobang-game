#include <graphics.h> 
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
enum GameState {
    MENU,
    LOGIN,
    MODE_SELECTION,
    PVP_MODE,
    PVE_MODE,
    GAME_OVER
};
GameState currentState;

// �û�����
struct UserData {
    string username;
    string password;
    string wins; // �˻���ս��ʤ����
    string losses; // ʧ�ܴ���
    string loginTime; // ���е�¼ʱ��
};

// ���ܺ���
string encrypt(const string& data, int key) {
    string encryptedData = data;
    for (char& c : encryptedData) {
        c *= key;
    }
    return encryptedData;
}

// ���ܺ���
string decrypt(const string& encryptedData, int key) {
    string decryptedData = encryptedData;
    for (char& c : decryptedData) {
        c /= key;
    }
    return decryptedData;
}

// �����û����ݵ��ļ�
void saveUserData(const UserData& user) {
    ofstream file(user.username + ".txt");
    if (file.is_open()) {
        file << user.username << endl;
        file << user.password << endl;
        file << user.wins << endl;
        file << user.losses << endl;
        file << user.loginTime << endl;
        file.close();
    }
    else {
        cerr << "Unable to open file for writing.\n";
    }
}

// ע���û�
void registerUser() {
    UserData user;
    cout << "Enter username: ";
    cin >> user.username;
    string password;
    cout << "Enter password: ";
    cin >> password;

   // ��ȡϵͳʱ����Ϊ��¼ʱ��
    time_t result = time(nullptr);
    string loginTime = asctime(std::localtime(&result));
    loginTime.pop_back(); // �Ƴ�ĩβ�Ļ��з�

  // ʹ���û�����Ϊ��Կ�����������
    int key = static_cast<int>(user.username.length());
    user.password = encrypt(password, key);

   // ����wins��losses��0�����û������Ե�½ʱ����м���
    user.wins = encrypt("0", password.length());
    user.losses = encrypt("0", password.length());
    user.loginTime = encrypt(loginTime, password.length());

   // �����û����ݵ��ļ�
    saveUserData(user);

   // ���µ�ǰ��Ϸ״̬Ϊ��¼����
    currentState = LOGIN;
}

// �û���¼
bool loginUser(const string& username, const string& password) {
    // ���Դ��û������ļ�
    UserData user;
    std::ifstream file(username + ".txt");
    if (file.is_open()) {
        getline(file, user.username);
        getline(file, user.password);
        file.close();

      // ʹ���û�����Ϊ��Կ��������
        int key = static_cast<int>(username.length());
        string decryptedPassword = decrypt(user.password, key);

        // ��������Ƿ�ƥ��
        if (decryptedPassword == password) {
            cout << "Login successful!\n";
            return true;
        }
        else {
            cout << "Incorrect password.\n";
            return false;
        }
    }
    else {
        cout << "User not found.\n";
        return false;
    }
}


int main() {
    // ��ʼ��easyXͼ�δ���
    // ...
    // ���ó�ʼ��Ϸ״̬ΪMENU
    currentState = MENU;

    // ����ע����¼ʾ��
    cout << "Do you want to register a new user? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        registerUser();
    }
    else {
        string username;
        string password;
        cout << "Enter username to login: ";
        cin >> username;
        cout << "Enter password to login: ";
        cin >> password;
        loginUser(username, password);
    }


    return 0;
}
