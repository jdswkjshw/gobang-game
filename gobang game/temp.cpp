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
//// ����һЩȫ�ֱ���������Ļ��С��
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// �����ı���Ͱ�ť�ĳߴ�λ��
//const int TEXTBOX_WIDTH = 200;
//const int TEXTBOX_HEIGHT = 30;
//const int BUTTON_WIDTH = 100;
//const int BUTTON_HEIGHT = 30;
//const int BUTTON_SPACING = 10; // ��ť���
//
//// �����ı���Ͱ�ť��λ��
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
//// ���������ַ������洢�û�������û���������
//std::string usernameInput = "";
//std::string passwordInput = "";
//
//// ��ǰѡ�е��ı���0: ��, 1: �û���, 2: ���룩
//int selectedInputBox = 0;
//// ʡ��֮ǰ��ö�ٺͽṹ�嶨��...
//enum GameState {
//    MENU,
//    LOGIN,
//    MODE_SELECTION,
//    PVP_MODE,
//    PVE_MODE,
//    GAME_OVER
//};
//GameState currentState;
//// �û����ݽṹ
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
//// ���ܺ���
//std::string encrypt(const std::string& data, int key) {
//    std::string encryptedData = data;
//    for (char& c : encryptedData) {
//        c *= key;
//    }
//    return encryptedData;
//}
//
//// ���ܺ���
//std::string decrypt(const std::string& encryptedData, int key) {
//    std::string decryptedData = encryptedData;
//    for (char& c : decryptedData) {
//        c /= key;
//    }
//    return decryptedData;
//}
//
//// �����û����ݵ��ļ�
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
//// �û�ע��ĺ���
//bool registerUser(const std::string& username, const std::string& password) {
//    UserData user;
//    std::cout << "Enter username: ";
//    std::cin >> user.username;
//    std::cout << "Enter password: ";
//    std::cin >> user.password;
//
//    // ��ȡϵͳʱ����Ϊ��¼ʱ��
//    std::time_t result = std::time(nullptr); // ��ȡ��ǰʱ��
//    std::tm loc_time;
//    localtime_s(&loc_time, &result); // �� time_t ���ת��Ϊ tm �ṹ�壬����ȫ�İ汾Ϊ localtime_s
//
//    char buffer[26]; // asctime_s ��Ҫһ���㹻��Ļ�����
//    asctime_s(buffer, sizeof(buffer), &loc_time); // ʹ�� asctime_s ��ȫ��ת�� tm �ṹ���ַ���
//
//    std::string loginTime = buffer; // ��������Ƶ� std::string
//    loginTime.pop_back(); // �Ƴ�ĩβ�Ļ��з�
//
//    // ʹ���û�����Ϊ��Կ�����������
//    int key = static_cast<int>(user.username.length());
//    user.password = encrypt(password, key);
//
//    // ����wins��losses��0�����û������Ե�½ʱ����м���
//    user.encryptedWins = encrypt("0", password.length());
//    user.encryptedLosses = encrypt("0", password.length());
//    user.encryptedLoginTime = encrypt(loginTime, password.length());
//
//    // �����û����ݵ��ļ�
//    saveUserData(user);
//
//    // ���µ�ǰ��Ϸ״̬Ϊ��¼����
//    currentState = LOGIN;
//    return true;
//}
//
//// �û���¼�ĺ���
//bool loginUser(const std::string& username, const std::string& password) {
//    UserData user;
//    std::ifstream file(username + ".txt");
//    if (file.is_open()) {
//        std::getline(file, user.username);
//        std::getline(file, user.password);
//        file.close();
//
//        // ʹ���û�����Ϊ��Կ��������
//        int key = static_cast<int>(username.length());
//        std::string decryptedPassword = decrypt(user.password, key);
//
//        // ��������Ƿ�ƥ��
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
//// �������̵ĺ���
//void drawChessboard() {
//    // ʡ�����̻����߼�...
//    //MessageBox(GetHWnd(), "Now entering the chessboard.", "Info", MB_OK);
//}
//
//// �����ı���
//void drawTextBox(RECT rect, const std::string& text, bool selected) {
//    setfillstyle(BS_SOLID); // ���������ʽ
//    setbkmode(TRANSPARENT); // ���ñ���͸��
//    setlinecolor(selected ? BLUE : BLACK); // ����ı���ѡ�У���߿�Ϊ��ɫ������Ϊ��ɫ
//    rectangle(rect.left, rect.top, rect.right, rect.bottom); // ���ƾ��ο�
//
//    // ת���ı�������λ��
//    std::wstring wtext = AnsiToWString(text.c_str()); // ���ı�ת��Ϊ���ַ���
//    int textX = rect.left + (TEXTBOX_WIDTH - textwidth(wtext.c_str())) / 2;
//    int textY = rect.top + (TEXTBOX_HEIGHT - textheight(wtext.c_str())) / 2;
//
//    outtextxy(textX, textY, wtext.c_str()); // �����ı�
//}
//
//// ���ư�ť
//void drawButton(RECT rect, const char* buttonText) {
//    setlinecolor(BLACK);
//    rectangle(rect.left, rect.top, rect.right, rect.bottom);
//
//    // ʹ�� AnsiToWString ����ת�� buttonText
//    std::wstring wButtonText = AnsiToWString(buttonText);
//
//    // ��Ҫע����ǣ�textwidth �� textheight ������Ҫ EasyX ��֧�ֿ��ַ���
//    outtextxy(rect.left + (BUTTON_WIDTH - textwidth(wButtonText.c_str())) / 2,
//        rect.top + (BUTTON_HEIGHT - textheight(wButtonText.c_str())) / 2,
//        wButtonText.c_str());
//}
//
//// ��¼������¼�������
//void handleLoginInterface() {
//    cleardevice(); // ����
//
//    // ���Ʊ���
//    settextstyle(30, 0, _T("Arial"));
//    outtextxy((SCREEN_WIDTH - textwidth(_T("User Login"))) / 2, 80, _T("User Login"));
//
//    // �����û����������ı���
//    settextstyle(16, 0, _T("Arial"));
//    drawTextBox(usernameRect, usernameInput, selectedInputBox == 1);
//    drawTextBox(passwordRect, std::string(passwordInput.length(), '*'), selectedInputBox == 2);
//
//    // ���Ƶ�¼��ť
//    drawButton(loginButtonRect, "Login");
//
//    FlushBatchDraw(); // ˢ����Ļ����
//}
//
//// ������
//int main() {
//    // ��ʼ��ͼ�ν���
//    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
//    setbkcolor(WHITE);
//    cleardevice();
//    BeginBatchDraw();
//
//    // ���õ�ǰ״̬Ϊ��¼
//    GameState currentState = LOGIN;
//    bool exitLoop = false;
//
//    // ��ѭ��
//    while (!exitLoop) {
//        switch (currentState) {
//        case LOGIN: {
//            handleLoginInterface();
//            break;
//        }
//                  // ʡ������case
//        default: {
//            break;
//        }
//        }
//
//        // ˢ����Ļ����
//        FlushBatchDraw();
//
//        // �����������
//        if (_kbhit()) {
//            char ch = _getch();
//            // ʡ���ı������봦��...
//        }
//
//        // ����������¼�
//        if (MouseHit()) {
//            auto m = GetMouseMsg();
//            switch (m.uMsg) {
//            case WM_LBUTTONDOWN: {
//                // ��¼��ť
//                if (PtInRect(&loginButtonRect, { m.x, m.y })) {
//                    // У���û���������
//                    if (loginUser(usernameInput, passwordInput)) {
//                        // ��¼�ɹ�����������
//                        drawChessboard();
//                        exitLoop = true; // ����ѭ����������Ϸ
//                    }
//                    else {
//                        MessageBox(GetHWnd(), TEXT("Login failed. Please try again."), TEXT("Error"), MB_ICONERROR);
//
//                    }
//                }
//                // ע�ᰴť
//                else if (PtInRect(&registerButtonRect, { m.x, m.y })) {
//                    // ע���û�
//                    if (registerUser(usernameInput, passwordInput)) {
//                        // ע��ɹ�����������
//                        drawChessboard();
//                        exitLoop = true; // ����ѭ����������Ϸ
//                    }
//                }
//                // ������ť
//                else if (PtInRect(&skipButtonRect, { m.x, m.y })) {
//                    // ֱ�ӻ�������
//                    drawChessboard();
//                    exitLoop = true; // ����ѭ����������Ϸ
//                }
//                break;
//            }
//            }
//        }
//    }
//
//    // ������ͼģʽ
//    EndBatchDraw();
//    closegraph();
//    return 0;
//}
