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

#ifndef KENG_OBJ_TYPES_CURSOR_HPP_INCLUDED
#define KENG_OBJ_TYPES_CURSOR_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "sprite.hpp"
#include "../main/obj_type_index.hpp"

///>
#define DEFAULT_ORDER_INDEX 0
///<

#define OBJECT_TYPE_CURSOR UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TCursor : public TComponent {
    private:
        TSprite* sprite;

        virtual void update();

    public:
        TCursor(TFrame* baseFrame /*!= 0*/,
                unsigned orderIndex = DEFAULT_ORDER_INDEX);
};

}

#undef DEFAULT_ORDER_INDEX

#endif // KENG_OBJ_TYPES_CURSOR_HPP_INCLUDED
