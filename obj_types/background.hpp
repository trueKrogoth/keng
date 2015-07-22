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

#ifndef KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED
#define KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "../main/obj_type_index.hpp"
#include <gl/gl.h>

#define DEFS\
        TBasis* baseObject,\
        unsigned orderIndex = 0\

#define ARGS\
        TBasis* baseObject,\
        unsigned orderIndex\

#define VALS\
        baseObject,\
        orderIndex\

#define TBACKGROUND_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CBACKGROUND_VALS VALS

namespace Keng {

class TBackground : public TComponent {
    private:
        virtual void update();

    protected:
        TBackground(IM_ARGS(ARGS));

    public:
        TBackground(DEFS);
};

inline TBackground::TBackground(IM_ARGS(ARGS)) : TComponent(IM_VALS(CCOMPONENT_VALS)) {
}

inline TBackground::TBackground(ARGS) : TBackground(IM_VALS(VALS)) {
}

inline void TBackground::update() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.0f, .0f, .0f, 1.0f);
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED
