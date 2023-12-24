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

// 用户数据
struct UserData {
    string username;
    string password;
    string wins; // 人机对战获胜次数
    string losses; // 失败次数
    string loginTime; // 所有登录时间
};

// 加密函数
string encrypt(const string& data, int key) {
    string encryptedData = data;
    for (char& c : encryptedData) {
        c *= key;
    }
    return encryptedData;
}

// 解密函数
string decrypt(const string& encryptedData, int key) {
    string decryptedData = encryptedData;
    for (char& c : decryptedData) {
        c /= key;
    }
    return decryptedData;
}

// 保存用户数据到文件
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

// 注册用户
void registerUser() {
    UserData user;
    cout << "Enter username: ";
    cin >> user.username;
    string password;
    cout << "Enter password: ";
    cin >> password;

   // 获取系统时间作为登录时间
    time_t result = time(nullptr);
    string loginTime = asctime(std::localtime(&result));
    loginTime.pop_back(); // 移除末尾的换行符

  // 使用用户名作为密钥进行密码加密
    int key = static_cast<int>(user.username.length());
    user.password = encrypt(password, key);

   // 假设wins和losses是0（新用户），对登陆时间进行加密
    user.wins = encrypt("0", password.length());
    user.losses = encrypt("0", password.length());
    user.loginTime = encrypt(loginTime, password.length());

   // 保存用户数据到文件
    saveUserData(user);

   // 更新当前游戏状态为登录界面
    currentState = LOGIN;
}

// 用户登录
bool loginUser(const string& username, const string& password) {
    // 尝试打开用户数据文件
    UserData user;
    std::ifstream file(username + ".txt");
    if (file.is_open()) {
        getline(file, user.username);
        getline(file, user.password);
        file.close();

      // 使用用户名作为密钥解密密码
        int key = static_cast<int>(username.length());
        string decryptedPassword = decrypt(user.password, key);

        // 检查密码是否匹配
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
    // 初始化easyX图形窗口
    // ...
    // 设置初始游戏状态为MENU
    currentState = MENU;

    // 进行注册或登录示例
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
