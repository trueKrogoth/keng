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

#include "world.hpp"
#include "../main/prog.hpp"
#include "../support/error.hpp"

using namespace Keng;

TWorld::TWorld(TObject* baseObject, int orderSize,
               int scrollSpeed, int scrollBorder, int startX, int startY,
               int __typeIndex) : TFrame(baseObject, orderSize, __typeIndex) {
    _scrollSpeed = scrollSpeed;
    _scrollBorder = scrollBorder;

    _x = startX;
    _y = startY;
}

void TWorld::update() {
    if (Prog::mouseX < scrollBorder)
        scrollLeft();
    if (Prog::mouseX > Prog::displayWidth - scrollBorder)
        scrollRight();
    if (Prog::mouseY < scrollBorder)
        scrollUp();
    if (Prog::mouseY > Prog::displayHeight - scrollBorder)
        scrollDown();
}

void TWorld::scrollLeft() {
    if (_x < scrollSpeed)
        _x = 0;
    else
        _x -= scrollSpeed;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipX();
}

void TWorld::scrollRight() {
    if (_x + scrollSpeed > tilebox->cornerX)
        _x = tilebox->cornerX;
    else
        _x += scrollSpeed;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipX();
}

void TWorld::scrollUp() {
    if (_y < scrollSpeed)
        _y = 0;
    else
        _y -= scrollSpeed;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipY();
}

void TWorld::scrollDown() {
    if (_y + scrollSpeed > tilebox->cornerY)
        _y = tilebox->cornerY;
    else
        _y += scrollSpeed;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipY();
}
