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

TWorld::TWorld(TObject* baseObject, unsigned orderSize, int boundRight, int boundBottom, int startX, int startY) :
               TFrame(baseObject, orderSize, boundRight, boundBottom, startX, startY) {
               initTypeIndex(OBJECT_TYPE_WORLD);
}

void TWorld::update() {
}

void TWorld::setX(int x) {
    _x = x;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipX();
}

void TWorld::setY(int y) {
    _y = y;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipY();
}
