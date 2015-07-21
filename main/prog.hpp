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

#include <tchar.h>
#include <windows.h>
#include <gl/gl.h>

namespace Keng {

class Prog {
    static const char* _name;
    static const char* _title;
    static unsigned int _frameTime;
    static BYTE colorBits;
    static BYTE zBufferBits;

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
        static constexpr unsigned int const& frameTime = _frameTime;

        static constexpr int const& displayWidth = _displayWidth;
        static constexpr int const& displayHeight = _displayHeight;
        static constexpr float const& displayAspectRatio = _displayAspectRatio;
        static constexpr int const& displayCenterX = _displayCenterX;
        static constexpr int const& displayCenterY = _displayCenterY;
        static constexpr int const& mouseX = _mouseX;
        static constexpr int const& mouseY = _mouseY;

        static void init(const char* name, const char* title, unsigned int frameTime, BYTE colorBits, BYTE zBufferBits);
        static int WINAPI main(HINSTANCE hThisInstance,
                               HINSTANCE hPrevInstance,
                               LPSTR lpszArgument,
                               int nCmdShow);
};

}

#endif // KENG_MAIN_PROG_HPP_INCLUDED
