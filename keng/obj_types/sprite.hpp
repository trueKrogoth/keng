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

#ifndef KENG_OBJ_TYPES_SPRITE_HPP_INCLUDED
#define KENG_OBJ_TYPES_SPRITE_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "frame.hpp"
#include "../main/obj_type_index.hpp"
#include "../support/spriteset.hpp"
#include "../support/graphics.hpp"

#define DEFS\
        TFrame* baseObject,\
        unsigned orderIndex = 0,\
        spriteset_t* spriteset = Spriteset::file("cursor.spr"),\
        int startX = 0,\
        int startY = 0

#define ARGS\
        TFrame* baseObject,\
        unsigned orderIndex,\
        spriteset_t* spriteset,\
        int startX,\
        int startY

#define VALS\
        baseObject,\
        orderIndex,\
        spriteset,\
        startX,\
        startY

#define TSPRITE_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CSPRITE_VALS VALS

namespace Keng {

class TSprite : public TComponent {
    private:
        spriteset_t* _spriteset;

        int _x;
        int _y;

        unsigned column;
        unsigned row;
        float scale;
        bool mirrorX;
        bool mirrorY;

        virtual void update();

    protected:
        TSprite(IM_ARGS(ARGS));

    public:
        spriteset_t* const& spriteset = _spriteset;

        int const& x = _x;
        int const& y = _y;

        TSprite(DEFS);

        void setSpriteset(spriteset_t* spriteset);
        void setCoords(int x, int y);
};

inline TSprite::TSprite(IM_ARGS(ARGS)) : TComponent(IM_VALS(CCOMPONENT_VALS)) {
    _spriteset = spriteset;

    _x = startX;
    _y = startY;

#if SAFE_MODE
    column = 0;
    row = 0;
    scale = 1.0f;
    mirrorX = false;
    mirrorY = false;
#endif
}

inline TSprite::TSprite(ARGS) : TSprite(IM_VALS(VALS)) {
}

inline void TSprite::update() {
    glLoadIdentity();
    glTranslatef(x - BFRAME->x, y - BFRAME->y, .0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    DrawSprite(spriteset, column, row, scale, mirrorX, mirrorY);
}

inline void TSprite::setSpriteset(spriteset_t* spriteset) {
    _spriteset = spriteset;
}

inline void TSprite::setCoords(int x, int y) {
    _x = x;
    _y = y;
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_SPRITE_HPP_INCLUDED
