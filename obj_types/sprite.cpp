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

#include "sprite.hpp"
#include "../support/graphics.hpp"
#include "../support/error.hpp"

using namespace Keng;

TSprite::TSprite(TFrame* baseFrame, int orderIndex,
                 spriteset_t* spriteset, int startX, int startY,
                 int __typeIndex) : TComponent(baseFrame, orderIndex, __typeIndex)
             #if SAFE_MODE
               , column(0), row(0), scale(1.0f), mirrorX(false), mirrorY(false)
             #endif
                {
    _spriteset = spriteset;

    _x = startX;
    _y = startY;
}

void TSprite::update() {
    glLoadIdentity();
    glTranslatef(x - static_cast<TFrame*>(baseObject)->x, y - static_cast<TFrame*>(baseObject)->y, .0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    DrawSprite(spriteset, column, row, scale, mirrorX, mirrorY);
}
