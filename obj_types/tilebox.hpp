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
#define DEFAULT_TILESET new tileset_t("barrens.tls")
#define DEFAULT_TILES_X 100
#define DEFAULT_TILES_Y 100
///<

#define OBJECT_TYPE_TILEBOX UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TTilebox : public TComponent {
    private:
        tileset_t* _tileset;

        int _tilesX;
        int _tilesY;

        int _cornerX;
        int _cornerY;

        int ** _tile;

        int leftClip;
        int rightClip;
        int topClip;
        int bottomClip;

        virtual void update();

    public:
        tileset_t* const& tileset = _tileset;
        int const& tilesX = _tilesX;
        int const& tilesY = _tilesY;

        int const& cornerX = _cornerX;
        int const& cornerY = _cornerY;

        int ** const& tile = _tile;

        TTilebox(TFrame* baseFrame /*!= 0*/,
                 int orderIndex = DEFAULT_ORDER_INDEX,
                 tileset_t* tileset = DEFAULT_TILESET,
                 int tilesX = DEFAULT_TILES_X,
                 int tilesY = DEFAULT_TILES_Y,
                 int __typeIndex = UNIQUE_OBJECT_TYPE_INDEX);

        void generate();

        void updateClipX();
        void updateClipY();
};

}

#undef DEFAULT_ORDER_INDEX
#undef DEFAULT_TILESET
#undef DEFAULT_TILES_X
#undef DEFAULT_TILES_Y

#endif // KENG_OBJ_TYPES_TILEBOX_HPP_INCLUDED
