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
    static int _displayAspectRatio;
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
        static const char* const& name;
        static const char* const& title;
        static unsigned int const& frameTime;

        static int const& displayWidth;
        static int const& displayHeight;
        static float const& displayAspectRatio;
        static int const& displayCenterX;
        static int const& displayCenterY;
        static int const& mouseX;
        static int const& mouseY;

        static void init(const char* name, const char* title, unsigned int frameTime, BYTE colorBits, BYTE zBufferBits);
        static int WINAPI main(HINSTANCE hThisInstance,
                               HINSTANCE hPrevInstance,
                               LPSTR lpszArgument,
                               int nCmdShow);
};

}

#endif // KENG_MAIN_PROG_HPP_INCLUDED
