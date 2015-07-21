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

///>
#define DEFAULT_ORDER_INDEX 0
#define DEFAULT_SPRITESET new spriteset_t("cursor.spr")
#define DEFAULT_START_X 0
#define DEFAULT_START_Y 0
///<

#define OBJECT_TYPE_SPRITE UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TSprite : public TComponent {
    private:
        virtual void update();

    protected:
        spriteset_t* _spriteset;

        int _x;
        int _y;

        int column;
        int row;
        float scale;
        bool mirrorX;
        bool mirrorY;

    public:
        spriteset_t* const& spriteset = _spriteset;

        int const& x = _x;
        int const& y = _y;

        TSprite(TFrame* baseFrame /*!= 0*/,
                int orderIndex = DEFAULT_ORDER_INDEX,
                spriteset_t* spriteset = DEFAULT_SPRITESET,
                int startX = DEFAULT_START_X,
                int startY = DEFAULT_START_Y,
                int __typeIndex = UNIQUE_OBJECT_TYPE_INDEX);

        inline void setSpriteset(spriteset_t* spriteset) {_spriteset = spriteset;};
        inline void setCoords(int x, int y) {_x = x; _y = y;};
};

}

#undef DEFAULT_ORDER_INDEX
#undef DEFAULT_SPRITESET
#undef DEFAULT_START_X
#undef DEFAULT_START_Y

#endif // KENG_OBJ_TYPES_SPRITE_HPP_INCLUDED
