#pragma once
#include <iostream>
#include <Windows.h>


namespace Misc {
    void MoveCenter()
    {
        RECT rectClient, rectWindow;
        HWND hWnd = GetConsoleWindow();
        GetClientRect(hWnd, &rectClient);
        GetWindowRect(hWnd, &rectWindow);
        int posx, posy;
        posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
            posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

            MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
    }

    HWND hwnd = GetConsoleWindow();


    void RemoveExtras()
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(handle, &info);
        COORD new_size =
        {
            info.srWindow.Right - info.srWindow.Left + 1,
            info.srWindow.Bottom - info.srWindow.Top + 1
        };
        SetConsoleScreenBufferSize(handle, new_size);

        LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        SetWindowLong(hwnd, GWL_STYLE, lStyle);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    }

    void PlayMusic(std::string audiofile_str) // play music lol
    {
        std::fstream fp;

        PlaySound(audiofile_str.c_str(), NULL, SND_FILENAME | SND_LOOP); //SND_FILENAME or SND_LOOP

        fp.close();
    }
}
