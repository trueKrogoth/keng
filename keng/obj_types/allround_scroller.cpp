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

#include "allround_scroller.hpp"
#include "../main/prog.hpp"

using namespace Keng;

TAllroundScroller::TAllroundScroller(TFrame* baseFrame, unsigned orderIndex,
                                     int scrollSpeed, int scrollBorder) :
                                     TComponent(baseFrame, orderIndex) {
                                     initTypeIndex(OBJECT_TYPE_ALLROUND_SCROLLER);
    _scrollSpeed = scrollSpeed;
    _scrollBorder = scrollBorder;
}

void TAllroundScroller::update() {
    if (Prog::mouseX < scrollBorder)
        scrollLeft();
    else
    if (Prog::mouseX > Prog::displayWidth - scrollBorder) {
        scrollRight();
    }
    if (Prog::mouseY < scrollBorder)
        scrollUp();
    else
    if (Prog::mouseY > Prog::displayHeight - scrollBorder)
        scrollDown();
}
