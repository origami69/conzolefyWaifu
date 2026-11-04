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


//c++ verzion 17 iz needed also legacy console is a must otherwise this wont work also look up how to implemenmnt the console by right clicking the top part of console then console properties and enabling legacy mode:
// Add-WindowsCapability -Online -Name Microsoft.Windows.Console.Legacy~~~~
//you can also change it by pressing command prompt then right click the top part and click settings and changing deafult terminal application to Windows Console Host and saving 
int main(int argc, char* argv[]) {
    // enter your folder path for the txt filez made in python
    std::string direc = "C:\\Users\\art\\Downloads\\gg";
    //enter path for your audio between the \"Path\"   //
    LPCSTR audioPath = "open \"C:\\Users\\art\\Downloads\\mmm.mp3\" type mpegvideo alias bruh";
    //put in the final number of the last text file
    int frameCount = 10128;
    //change fps accorddingly, make sure the fps set in python is same as mp3
    double fps = 60;

    CONSOLE_FONT_INFOEX cfi{};
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 4;
    cfi.dwFontSize.Y = 4;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Arial");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetCurrentConsoleFontEx(h, FALSE, &cfi);
    int k = 0;
    std::vector<std::string> bronya = {};
    bronya.reserve(frameCount);
    for (k; k < frameCount; k++) {
        std::string FILENAME = direc + (std::string)"\\frame" + std::to_string(k) + (std::string)".txt";
        std::ifstream f(FILENAME);
        if (f) {
            std::string s;
            std::string s2;
            std::string sTotal;
            if (!std::getline(f, s2)) {
                return 0;
            }
            while (std::getline(f, s)) {
                sTotal += s2 + "\n";
                s2 = s;
            }
            sTotal += s2;
            f.close();
            bronya.push_back(sTotal);
        }
    }
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo{};
    if (!GetConsoleScreenBufferInfo(h, &bufferInfo)) {
        std::cerr << "Failed to get console information.\n";
        return 1;
    }
    if (mciSendStringA(audioPath, nullptr, 0, nullptr) != 0) {
        std::cerr << "Failed to open audio.\n";
        return 1;
    }
    mciSendStringA("play bruh", nullptr, 0, nullptr);
    using t = std::chrono::steady_clock;
    const auto start = t::now();
    for (int i = 0; i < frameCount; i++) {
        SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
        WriteConsoleA(h,bronya[i].data(),static_cast<DWORD>(bronya[i].size()),0,nullptr);
        const auto target = start + std::chrono::duration_cast<t::duration>(std::chrono::duration<double>(i / fps));
        std::this_thread::sleep_until(target);
    }
    mciSendStringA("close bruh", nullptr, 0, nullptr);
    return 0;
}
