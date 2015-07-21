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

#include "frame.hpp"

using namespace Keng;

TFrame::TFrame(TObject* baseObject, int orderSize,
               int boundRight, int boundBottom, int startX, int startY) :
               TBasis(baseObject, orderSize) {
               initTypeIndex(OBJECT_TYPE_FRAME);
    _boundRight = boundRight;
    _boundBottom = boundBottom;

    _x = startX;
    _y = startY;
}

void TFrame::update() {
}
