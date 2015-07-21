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

#ifndef KENG_OBJ_TYPES_WORLD_HPP_INCLUDED
#define KENG_OBJ_TYPES_WORLD_HPP_INCLUDED

#include "frame.hpp"
#include "tilebox.hpp"
#include "../main/obj_type_index.hpp"

///>
#define DEFAULT_ORDER_SIZE 10
#define DEFAULT_SCROLL_SPEED 30
#define DEFAULT_SCROLL_BORDER 15
#define DEFAULT_START_X 0
#define DEFAULT_START_Y 0
///<

#define OBJECT_TYPE_WORLD UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TWorld : public TFrame {
    private:
        virtual void update();

    protected:
        TTilebox* _tilebox;

        int _scrollSpeed;
        int _scrollBorder;

    public:
        TTilebox* const& tilebox = _tilebox;

        int const& scrollSpeed = _scrollSpeed;
        int const& scrollBorder = _scrollBorder;

        TWorld(TObject* baseObject = 0,
               int orderSize = DEFAULT_ORDER_SIZE,
               int scrollSpeed = DEFAULT_SCROLL_SPEED,
               int scrollBorder = DEFAULT_SCROLL_BORDER,
               int startX = DEFAULT_START_X,
               int startY = DEFAULT_START_Y,
               int __typeIndex = UNIQUE_OBJECT_TYPE_INDEX);

        void setTilebox(TTilebox* tilebox) {_tilebox = tilebox;};

        void scrollLeft();
        void scrollRight();
        void scrollUp();
        void scrollDown();
};

}

#undef DEFAULT_ORDER_SIZE
#undef DEFAULT_SCROLL_SPEED
#undef DEFAULT_SCROLL_BORDER
#undef DEFAULT_START_X
#undef DEFAULT_START_Y

#endif // KENG_OBJ_TYPES_WORLD_HPP_INCLUDED
