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

using namespace Keng;

const char* Prog::_name;
const char* Prog::_title;
unsigned Prog::_frameTime;
unsigned char Prog::_colorBits;
unsigned char Prog::_zBufferBits;

int Prog::_displayWidth;
int Prog::_displayHeight;
float Prog::_displayAspectRatio;
int Prog::_displayCenterX;
int Prog::_displayCenterY;

int Prog::_mouseX;
int Prog::_mouseY;

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
            onCreate();
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
