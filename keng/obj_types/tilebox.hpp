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

#ifndef KENG_OBJ_TYPES_TILEBOX_HPP_INCLUDED
#define KENG_OBJ_TYPES_TILEBOX_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "frame.hpp"
#include "../main/obj_type_index.hpp"
#include "../support/tileset.hpp"

///>
#define DEFAULT_ORDER_INDEX 0
#define DEFAULT_TILESET Tileset::file("barrens.tls")
#define DEFAULT_TILES_X 100
#define DEFAULT_TILES_Y 100
///<

#define OBJECT_TYPE_TILEBOX UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TTilebox : public TComponent {
    private:
        tileset_t* _tileset;

        unsigned _tilesX;
        unsigned _tilesY;

        unsigned ** _tile;

        unsigned leftClip;
        unsigned rightClip;
        unsigned topClip;
        unsigned bottomClip;

        virtual void update();

    public:
        tileset_t* const& tileset = _tileset;

        unsigned const& tilesX = _tilesX;
        unsigned const& tilesY = _tilesY;

        unsigned ** const& tile = _tile;

        TTilebox(TFrame* baseFrame /*!= 0*/,
                 unsigned orderIndex = DEFAULT_ORDER_INDEX,
                 tileset_t* tileset = DEFAULT_TILESET,
                 unsigned tilesX = DEFAULT_TILES_X,
                 unsigned tilesY = DEFAULT_TILES_Y);

        void generate();

        void updateClipX();
        void updateClipY();
};

inline void TTilebox::updateClipX() {
    leftClip = static_cast<TFrame*>(baseObject)->x * tileset->tileInverseWidth;
    rightClip = leftClip + tileset->clipTilesX;
    if (rightClip > tilesX)
        rightClip = tilesX;
}

inline void TTilebox::updateClipY() {
    topClip = static_cast<TFrame*>(baseObject)->y * tileset->tileInverseHeight;
    bottomClip = topClip + tileset->clipTilesY;
    if (bottomClip > tilesY)
        bottomClip = tilesY;
}

}

#undef DEFAULT_ORDER_INDEX
#undef DEFAULT_TILESET
#undef DEFAULT_TILES_X
#undef DEFAULT_TILES_Y

#endif // KENG_OBJ_TYPES_TILEBOX_HPP_INCLUDED
