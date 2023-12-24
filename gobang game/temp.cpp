//#include <graphics.h>
//#include <conio.h>
//#include <fstream>
//#include <iostream>
//#include <ctime>
//#include <string>
//#include <Windows.h>
//#include<vector>
//
//std::wstring AnsiToWString(const char* cstr) {
//    if (cstr == nullptr) return std::wstring();
//    int len = MultiByteToWideChar(CP_UTF8, 0, cstr, -1, nullptr, 0);
//    if (len == 0) return std::wstring();
//    std::vector<wchar_t> wstr(len);
//    MultiByteToWideChar(CP_UTF8, 0, cstr, -1, &wstr[0], len);
//    return std::wstring(wstr.begin(), wstr.end() - 1); // remove null terminator
//}
//
//// 定义一些全局变量，如屏幕大小等
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// 定义文本框和按钮的尺寸位置
//const int TEXTBOX_WIDTH = 200;
//const int TEXTBOX_HEIGHT = 30;
//const int BUTTON_WIDTH = 100;
//const int BUTTON_HEIGHT = 30;
//const int BUTTON_SPACING = 10; // 按钮间距
//
//// 定义文本框和按钮的位置
//RECT usernameRect = { SCREEN_WIDTH / 2 - TEXTBOX_WIDTH / 2,
//                     SCREEN_HEIGHT / 2 - TEXTBOX_HEIGHT - 20,
//                     SCREEN_WIDTH / 2 + TEXTBOX_WIDTH / 2,
//                     SCREEN_HEIGHT / 2 };
//
//RECT passwordRect = { SCREEN_WIDTH / 2 - TEXTBOX_WIDTH / 2,
//                     SCREEN_HEIGHT / 2 + 20,
//                     SCREEN_WIDTH / 2 + TEXTBOX_WIDTH / 2,
//                     SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT + 20 };
//
//RECT loginButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT + 60,
//                   SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + 2 * TEXTBOX_HEIGHT + 60 };
//RECT registerButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT + 60,
//                   SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + 2 * TEXTBOX_HEIGHT + 60 };
//RECT skipButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + TEXTBOX_HEIGHT + 60,
//                   SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2,
//                   SCREEN_HEIGHT / 2 + 2 * TEXTBOX_HEIGHT + 60 };
//
//// 定义两个字符串来存储用户输入的用户名和密码
//std::string usernameInput = "";
//std::string passwordInput = "";
//
//// 当前选中的文本框（0: 无, 1: 用户名, 2: 密码）
//int selectedInputBox = 0;
//// 省略之前的枚举和结构体定义...
//enum GameState {
//    MENU,
//    LOGIN,
//    MODE_SELECTION,
//    PVP_MODE,
//    PVE_MODE,
//    GAME_OVER
//};
//GameState currentState;
//// 用户数据结构
//struct UserData {
//    std::string username;
//    std::string password;
//    std::string encryptedWins;
//    std::string encryptedLosses;
//    std::string encryptedLoginTime;
//};
//
//
//
//
//// 加密函数
//std::string encrypt(const std::string& data, int key) {
//    std::string encryptedData = data;
//    for (char& c : encryptedData) {
//        c *= key;
//    }
//    return encryptedData;
//}
//
//// 解密函数
//std::string decrypt(const std::string& encryptedData, int key) {
//    std::string decryptedData = encryptedData;
//    for (char& c : decryptedData) {
//        c /= key;
//    }
//    return decryptedData;
//}
//
//// 保存用户数据到文件
//void saveUserData(const UserData & user) {
//    std::ofstream file(user.username + ".txt");
//    if (file.is_open()) {
//        file << user.username << std::endl;
//        file << user.password << std::endl;
//        file << user.encryptedWins << std::endl;
//        file << user.encryptedLosses << std::endl;
//        file << user.encryptedLoginTime << std::endl;
//        file.close();
//    }
//    else {
//        std::cerr << "Unable to open file for writing.\n";
//    }
//}
//
//// 用户注册的函数
//bool registerUser(const std::string& username, const std::string& password) {
//    UserData user;
//    std::cout << "Enter username: ";
//    std::cin >> user.username;
//    std::cout << "Enter password: ";
//    std::cin >> user.password;
//
//    // 获取系统时间作为登录时间
//    std::time_t result = std::time(nullptr); // 获取当前时间
//    std::tm loc_time;
//    localtime_s(&loc_time, &result); // 将 time_t 结果转换为 tm 结构体，更安全的版本为 localtime_s
//
//    char buffer[26]; // asctime_s 需要一个足够大的缓冲区
//    asctime_s(buffer, sizeof(buffer), &loc_time); // 使用 asctime_s 安全地转换 tm 结构到字符串
//
//    std::string loginTime = buffer; // 将结果复制到 std::string
//    loginTime.pop_back(); // 移除末尾的换行符
//
//    // 使用用户名作为密钥进行密码加密
//    int key = static_cast<int>(user.username.length());
//    user.password = encrypt(password, key);
//
//    // 假设wins和losses是0（新用户），对登陆时间进行加密
//    user.encryptedWins = encrypt("0", password.length());
//    user.encryptedLosses = encrypt("0", password.length());
//    user.encryptedLoginTime = encrypt(loginTime, password.length());
//
//    // 保存用户数据到文件
//    saveUserData(user);
//
//    // 更新当前游戏状态为登录界面
//    currentState = LOGIN;
//    return true;
//}
//
//// 用户登录的函数
//bool loginUser(const std::string& username, const std::string& password) {
//    UserData user;
//    std::ifstream file(username + ".txt");
//    if (file.is_open()) {
//        std::getline(file, user.username);
//        std::getline(file, user.password);
//        file.close();
//
//        // 使用用户名作为密钥解密密码
//        int key = static_cast<int>(username.length());
//        std::string decryptedPassword = decrypt(user.password, key);
//
//        // 检查密码是否匹配
//        if (decryptedPassword == password) {
//            std::cout << "Login successful!\n";
//            return true;
//        }
//        else {
//            std::cout << "Incorrect password.\n";
//            return false;
//        }
//    }
//    else {
//        std::cout << "User not found.\n";
//        return false;
//    }
//}
//
//// 绘制棋盘的函数
//void drawChessboard() {
//    // 省略棋盘绘制逻辑...
//    //MessageBox(GetHWnd(), "Now entering the chessboard.", "Info", MB_OK);
//}
//
//// 绘制文本框
//void drawTextBox(RECT rect, const std::string& text, bool selected) {
//    setfillstyle(BS_SOLID); // 设置填充样式
//    setbkmode(TRANSPARENT); // 设置背景透明
//    setlinecolor(selected ? BLUE : BLACK); // 如果文本框被选中，则边框为蓝色，否则为黑色
//    rectangle(rect.left, rect.top, rect.right, rect.bottom); // 绘制矩形框
//
//    // 转换文本并计算位置
//    std::wstring wtext = AnsiToWString(text.c_str()); // 将文本转换为宽字符串
//    int textX = rect.left + (TEXTBOX_WIDTH - textwidth(wtext.c_str())) / 2;
//    int textY = rect.top + (TEXTBOX_HEIGHT - textheight(wtext.c_str())) / 2;
//
//    outtextxy(textX, textY, wtext.c_str()); // 绘制文本
//}
//
//// 绘制按钮
//void drawButton(RECT rect, const char* buttonText) {
//    setlinecolor(BLACK);
//    rectangle(rect.left, rect.top, rect.right, rect.bottom);
//
//    // 使用 AnsiToWString 函数转换 buttonText
//    std::wstring wButtonText = AnsiToWString(buttonText);
//
//    // 需要注意的是，textwidth 和 textheight 函数需要 EasyX 库支持宽字符串
//    outtextxy(rect.left + (BUTTON_WIDTH - textwidth(wButtonText.c_str())) / 2,
//        rect.top + (BUTTON_HEIGHT - textheight(wButtonText.c_str())) / 2,
//        wButtonText.c_str());
//}
//
//// 登录界面的事件处理函数
//void handleLoginInterface() {
//    cleardevice(); // 清屏
//
//    // 绘制标题
//    settextstyle(30, 0, _T("Arial"));
//    outtextxy((SCREEN_WIDTH - textwidth(_T("User Login"))) / 2, 80, _T("User Login"));
//
//    // 绘制用户名和密码文本框
//    settextstyle(16, 0, _T("Arial"));
//    drawTextBox(usernameRect, usernameInput, selectedInputBox == 1);
//    drawTextBox(passwordRect, std::string(passwordInput.length(), '*'), selectedInputBox == 2);
//
//    // 绘制登录按钮
//    drawButton(loginButtonRect, "Login");
//
//    FlushBatchDraw(); // 刷新屏幕绘制
//}
//
//// 主函数
//int main() {
//    // 初始化图形界面
//    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
//    setbkcolor(WHITE);
//    cleardevice();
//    BeginBatchDraw();
//
//    // 设置当前状态为登录
//    GameState currentState = LOGIN;
//    bool exitLoop = false;
//
//    // 主循环
//    while (!exitLoop) {
//        switch (currentState) {
//        case LOGIN: {
//            handleLoginInterface();
//            break;
//        }
//                  // 省略其他case
//        default: {
//            break;
//        }
//        }
//
//        // 刷新屏幕绘制
//        FlushBatchDraw();
//
//        // 处理键盘输入
//        if (_kbhit()) {
//            char ch = _getch();
//            // 省略文本框输入处理...
//        }
//
//        // 处理鼠标点击事件
//        if (MouseHit()) {
//            auto m = GetMouseMsg();
//            switch (m.uMsg) {
//            case WM_LBUTTONDOWN: {
//                // 登录按钮
//                if (PtInRect(&loginButtonRect, { m.x, m.y })) {
//                    // 校验用户名和密码
//                    if (loginUser(usernameInput, passwordInput)) {
//                        // 登录成功，绘制棋盘
//                        drawChessboard();
//                        exitLoop = true; // 结束循环，进入游戏
//                    }
//                    else {
//                        MessageBox(GetHWnd(), TEXT("Login failed. Please try again."), TEXT("Error"), MB_ICONERROR);
//
//                    }
//                }
//                // 注册按钮
//                else if (PtInRect(&registerButtonRect, { m.x, m.y })) {
//                    // 注册用户
//                    if (registerUser(usernameInput, passwordInput)) {
//                        // 注册成功，绘制棋盘
//                        drawChessboard();
//                        exitLoop = true; // 结束循环，进入游戏
//                    }
//                }
//                // 跳过按钮
//                else if (PtInRect(&skipButtonRect, { m.x, m.y })) {
//                    // 直接绘制棋盘
//                    drawChessboard();
//                    exitLoop = true; // 结束循环，进入游戏
//                }
//                break;
//            }
//            }
//        }
//    }
//
//    // 结束绘图模式
//    EndBatchDraw();
//    closegraph();
//    return 0;
//}
