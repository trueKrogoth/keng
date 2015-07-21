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

#ifndef KENG_OBJ_TYPES_FRAME_HPP_INCLUDED
#define KENG_OBJ_TYPES_FRAME_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "../main/obj_type_index.hpp"

///>
#define DEFAULT_ORDER_SIZE 30
#define DEFAULT_BOUND_RIGHT 0
#define DEFAULT_BOUND_BOTTOM 0
#define DEFAULT_START_X 0
#define DEFAULT_START_Y 0
///<

#define OBJECT_TYPE_FRAME UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TFrame : public TBasis {
    private:
        virtual void update();

    protected:
        int _boundRight;
        int _boundBottom;

        int _x;
        int _y;

    public:
        int const& boundRight = _boundRight;
        int const& boundBottom = _boundBottom;

        int const& x = _x;
        int const& y = _y;

        TFrame(TObject* baseObject = 0,
               unsigned orderSize = DEFAULT_ORDER_SIZE,
               int boundRight = DEFAULT_BOUND_RIGHT,
               int boundBottom = DEFAULT_BOUND_BOTTOM,
               int startX = DEFAULT_START_X,
               int startY = DEFAULT_START_Y);

        virtual void setX(int x);
        virtual void setY(int y);
};

}

#undef DEFAULT_ORDER_SIZE
#undef DEFAULT_BOUND_RIGHT
#undef DEFAULT_BOUND_BOTTOM
#undef DEFAULT_START_X
#undef DEFAULT_START_Y

#endif // KENG_OBJ_TYPES_FRAME_HPP_INCLUDED
