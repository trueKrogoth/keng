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

#ifndef KENG_MAIN_PROG_HPP_INCLUDED
#define KENG_MAIN_PROG_HPP_INCLUDED

#include <windows.h>
#include <gl/gl.h>

namespace Keng {

class Prog {
    private:
        static const char* _name;
        static const char* _title;
        static unsigned _frameTime;
        static unsigned char _colorBits;
        static unsigned char _zBufferBits;

        static int _displayWidth;
        static int _displayHeight;
        static float _displayAspectRatio;
        static int _displayCenterX;
        static int _displayCenterY;

        static int _mouseX;
        static int _mouseY;

        static UINT_PTR timer;
        static HDC hDC;
        static HGLRC hRC;
        static PIXELFORMATDESCRIPTOR pfd;

        static LRESULT CALLBACK proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

        /*undefined*/ static void onTimer();
        /*undefined*/ static void onMouseMove();
        /*undefined*/ static void onRButtonDown(WPARAM button);
        /*undefined*/ static void onRButtonUp(WPARAM button);
        /*undefined*/ static void onKeyDown(WPARAM key);
        /*undefined*/ static void onKeyUp(WPARAM key);
        /*undefined*/ static void onCreate();
        /*undefined*/ static void onClose();

    public:
        static constexpr const char* const& name = _name;
        static constexpr const char* const& title = _title;
        static constexpr unsigned const& frameTime = _frameTime;
        static constexpr unsigned char const& colorBits = _colorBits;
        static constexpr unsigned char const& zBufferBits = _zBufferBits;

        static constexpr int const& displayWidth = _displayWidth;
        static constexpr int const& displayHeight = _displayHeight;
        static constexpr float const& displayAspectRatio = _displayAspectRatio;
        static constexpr int const& displayCenterX = _displayCenterX;
        static constexpr int const& displayCenterY = _displayCenterY;
        static constexpr int const& mouseX = _mouseX;
        static constexpr int const& mouseY = _mouseY;

        static void init(const char* name, const char* title, unsigned frameTime, unsigned char colorBits, unsigned char zBufferBits);
        static int WINAPI main(HINSTANCE hThisInstance,
                               HINSTANCE hPrevInstance,
                               LPSTR lpszArgument,
                               int nCmdShow);
};

inline void Prog::init(const char* name, const char* title, unsigned frameTime, unsigned char colorBits, unsigned char zBufferBits) {
    _name = name;
    _title = title;
    _frameTime = frameTime;
    _colorBits = colorBits;
    _zBufferBits = zBufferBits;

    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    _displayWidth = rect.right;
    _displayHeight = rect.bottom;
    _displayAspectRatio = (float) displayWidth / displayHeight;
    _displayCenterX = displayWidth * 0.5f;
    _displayCenterY = displayHeight * 0.5f;
}

inline int WINAPI Prog::main(HINSTANCE hThisInstance,
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

}

#endif // KENG_MAIN_PROG_HPP_INCLUDED
