// ClaSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <cwchar>
#include <vector>
#include <stdlib.h>
#include <filesystem>

#pragma comment(lib, "Winmm.lib")

//c++ verzion 17 iz needed
//zet the zcreen zize to max while it loadz
int main(int argc, char* argv[]) {
    // enter your folder path for the txt filez made in python
    std::string direc = "C:\\Users\\abece\\Downloads\\New folder\\mm\\gg";
    //enter path for your audio between the \"Path\"   //
    LPCSTR audioPath = "open \"C:\\Users\\abece\\Downloads\\New folder\\mm\\mmm.mp3\" type mpegvideo alias bruh";
    int frameCount = 0;
    for (auto& f : std::filesystem::directory_iterator(direc)){
        frameCount++;
    }
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 4;
    cfi.dwFontSize.Y = 4;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Arial"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    int k = 0;
    std::vector<std::string> bronya = {};
    for (k; k < frameCount; k++) {
        std::string FILENAME = direc + (std::string)"\\frame" + std::to_string(k) + (std::string)".txt";
        std::ifstream f(FILENAME);
        if (f) {
            std::string s;
            std::string sTotal;
            for (int i = 0; i < 200; i++) {
                std::getline(f, s);
                if (i != 199) { 
                    sTotal += s + "\n"; 
                } else {
                    sTotal += s;
                }
            }
            f.close();
            bronya.push_back(sTotal);
        }
    }
    mciSendStringA(audioPath, NULL, 0, NULL);
    mciSendStringA("play bruh", NULL, 0, NULL);
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    int i = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    for(i; i<frameCount;i++){
        SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
        std::cout << bronya.at(i);
        t += std::chrono::milliseconds(33);
        std::this_thread::sleep_until(t);
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
