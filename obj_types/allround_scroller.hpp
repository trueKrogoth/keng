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

#ifndef KENG_OBJ_TYPES_ALLROUND_SCROLLER_HPP_INCLUDED
#define KENG_OBJ_TYPES_ALLROUND_SCROLLER_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "frame.hpp"
#include "../main/obj_type_index.hpp"
#include "../main/prog.hpp"

#define DEFS\
        TFrame* baseObject,\
        unsigned orderIndex = 0,\
        int scrollSpeed = 30,\
        int scrollBorder = 15

#define ARGS\
        TFrame* baseObject,\
        unsigned orderIndex,\
        int scrollSpeed,\
        int scrollBorder

#define VALS\
        baseObject,\
        orderIndex,\
        scrollSpeed,\
        scrollBorder

#define TALLROUND_SCROLLER_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CALLROUND_SCROLLER_VALS VALS

namespace Keng {

class TAllroundScroller : public TComponent {
    private:
        virtual void update();

    protected:
        int _scrollSpeed;
        int _scrollBorder;

        TAllroundScroller(IM_ARGS(ARGS));

    public:
        int const& scrollSpeed = _scrollSpeed;
        int const& scrollBorder = _scrollBorder;

        TAllroundScroller(DEFS);
};

inline TAllroundScroller::TAllroundScroller(IM_ARGS(ARGS)) : TComponent(IM_VALS(CCOMPONENT_VALS)) {
    _scrollSpeed = scrollSpeed;
    _scrollBorder = scrollBorder;
}

inline TAllroundScroller::TAllroundScroller(ARGS) : TAllroundScroller(IM_VALS(VALS)) {
}

inline void TAllroundScroller::update() {
    if (Prog::mouseX < scrollBorder)
        BFRAME->setX(BFRAME->x - scrollSpeed);
    else
    if (Prog::mouseX > Prog::displayWidth - scrollBorder) {
        BFRAME->setX(BFRAME->x + scrollSpeed);
    }
    if (Prog::mouseY < scrollBorder)
        BFRAME->setY(BFRAME->y - scrollSpeed);
    else
    if (Prog::mouseY > Prog::displayHeight - scrollBorder)
        BFRAME->setY(BFRAME->y + scrollSpeed);
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_ALLROUND_SCROLLER_HPP_INCLUDED
