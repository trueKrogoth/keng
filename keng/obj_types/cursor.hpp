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
#include "frame.hpp"
#include "sprite.hpp"
#include "../main/obj_type_index.hpp"
#include "../main/prog.hpp"

#define DEFS\
        TFrame* baseObject,\
        unsigned orderIndex = 0\

#define ARGS\
        TFrame* baseObject,\
        unsigned orderIndex\

#define VALS\
        baseObject,\
        orderIndex\

#define TCURSOR_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CCURSOR_VALS VALS

namespace Keng {

class TCursor : public TComponent {
    private:
        TSprite* sprite;

        virtual void update();

    protected:
        TCursor(IM_ARGS(ARGS));

    public:
        TCursor(DEFS);
};

inline TCursor::TCursor(IM_ARGS(ARGS)) : TComponent(IM_VALS(CCOMPONENT_VALS)) {
    sprite = new TSprite(baseObject, 20, Spriteset::file("cursor.spr"));
}

inline TCursor::TCursor(ARGS) : TCursor(IM_VALS(VALS)) {
}

inline void TCursor::update() {
    sprite->setCoords(Prog::mouseX, Prog::mouseY);
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_CURSOR_HPP_INCLUDED
