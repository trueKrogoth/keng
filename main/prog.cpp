/*
 * Keng Engine
 * Copyright (C) 2015 Krogoth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <windowsx.h>
#include "prog.hpp"
#include "../obj_cfgs.hpp"

using namespace Keng;

const char* Prog::_name;
const char* const& Prog::name = Prog::_name;
const char* Prog::_title;
const char* const& Prog::title = Prog::_title;
unsigned int Prog::_frameTime;
unsigned int const& Prog::frameTime = Prog::_frameTime;
BYTE Prog::colorBits;
BYTE Prog::zBufferBits;

int Prog::_displayWidth;
int const& Prog::displayWidth = Prog::_displayWidth;
int Prog::_displayHeight;
int const& Prog::displayHeight = Prog::_displayHeight;
int Prog::_displayAspectRatio;
float const& Prog::displayAspectRatio = Prog::_displayAspectRatio;
int Prog::_displayCenterX;
int const& Prog::displayCenterX = Prog::_displayCenterX;
int Prog::_displayCenterY;
int const& Prog::displayCenterY = Prog::_displayCenterY;

int Prog::_mouseX;
int const& Prog::mouseX = Prog::_mouseX;
int Prog::_mouseY;
int const& Prog::mouseY = Prog::_mouseY;

UINT_PTR Prog::timer;
HDC Prog::hDC;
HGLRC Prog::hRC;
PIXELFORMATDESCRIPTOR Prog::pfd;

LRESULT CALLBACK Prog::proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_TIMER:
            glFlush();
            onTimer();
            SwapBuffers(hDC);
            return 0;
        case WM_MOUSEMOVE:
            _mouseX = GET_X_LPARAM(lParam);
            _mouseY = GET_Y_LPARAM(lParam);
            onMouseMove();
            return 0;
        case WM_RBUTTONDOWN:
            onRButtonDown(wParam);
            return 0;
        case WM_RBUTTONUP:
            onRButtonUp(wParam);
            return 0;
        case WM_KEYDOWN:
            onKeyDown(wParam);
            return 0;
        case WM_KEYUP:
            onKeyUp(wParam);
            return 0;
        case WM_CREATE:
            InitObjectPrescribedConfigs();
            onCreate();
            timer = SetTimer(hwnd, 1, frameTime, 0);
            hDC = GetDC(hwnd);
            pfd = {sizeof(PIXELFORMATDESCRIPTOR), //size of structure
                   1,                             //default version
                   PFD_DRAW_TO_WINDOW |           //window drawing support
                   PFD_SUPPORT_OPENGL |           //OpenGL support
                   PFD_DOUBLEBUFFER,              //double buffering support
                   PFD_TYPE_RGBA,                 //RGBA color mode
                   colorBits,                     //? bit color mode
                   0, 0, 0, 0, 0, 0,              //ignore color bits
                   0,                             //no alpha buffer
                   0,                             //ignore shift bit
                   0,                             //no accumulation buffer
                   0, 0, 0, 0,                    //ignore accumulation bits
                   zBufferBits,                   //? bit z-buffer size
                   0,                             //no stencil buffer
                   0,                             //no aux buffer
                   PFD_MAIN_PLANE,                //main drawing plane
                   0,                             //reserved
                   0, 0, 0                        //layer masks ignored
                   };
            SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
            hRC = wglCreateContext(hDC);
            wglMakeCurrent(hDC, hRC);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(.0f, displayWidth, displayHeight, .0f, .0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
            return 0;
        case WM_CLOSE:
            onClose();
            wglMakeCurrent(hDC, 0);
            wglDeleteContext(hRC);
            ReleaseDC(hwnd, hDC);
            KillTimer(hwnd, timer);
            ShowCursor(TRUE);
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

void Prog::init(const char* name, const char* title, unsigned int frameTime, BYTE colorBits, BYTE zBufferBits) {
    Prog::_name = name;
    Prog::_title = title;
    Prog::_frameTime = frameTime;
    Prog::colorBits = colorBits;
    Prog::zBufferBits = zBufferBits;

    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    _displayWidth = rect.right;
    _displayHeight = rect.bottom;
    _displayAspectRatio = (float) displayWidth / displayHeight;
    _displayCenterX = displayWidth * 0.5f;
    _displayCenterY = displayHeight * 0.5f;
}

int WINAPI Prog::main(HINSTANCE hThisInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpszArgument,
                      int nCmdShow) {
    MSG messages;
    WNDCLASSEX wincl;
    DEVMODE dmScreenSettings;

    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = displayWidth;
    dmScreenSettings.dmPelsHeight = displayHeight;
    dmScreenSettings.dmBitsPerPel = colorBits;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = name;
    wincl.lpfnWndProc = proc;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(0, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(0, IDI_WINLOGO);
    wincl.hCursor = LoadCursor(0, IDC_ARROW);
    wincl.lpszMenuName = 0;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = HBRUSH(COLOR_WINDOWTEXT);

    if (!RegisterClassEx(&wincl) || ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN != DISP_CHANGE_SUCCESSFUL))
        return 0;

    const HWND hwnd = CreateWindowEx(
            0,
            name,
            title,
            WS_POPUP,
            0,
            0,
            displayWidth,
            displayHeight,
            0,
            0,
            hThisInstance,
            0
            );
    ShowCursor(0);
    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, 0, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
