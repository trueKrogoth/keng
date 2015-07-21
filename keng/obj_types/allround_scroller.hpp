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

#ifndef KENG_OBJ_TYPES_DUMMY_HPP_INCLUDED
#define KENG_OBJ_TYPES_DUMMY_HPP_INCLUDED

#include "../main/obj_basic_types.hpp"
#include "frame.hpp"
#include "../main/obj_type_index.hpp"

///>
#define DEFAULT_ORDER_INDEX 0
#define DEFAULT_SCROLL_SPEED 30
#define DEFAULT_SCROLL_BORDER 15
///<

#define OBJECT_TYPE_ALLROUND_SCROLLER UNIQUE_OBJECT_TYPE_INDEX

namespace Keng {

class TAllroundScroller : public TComponent {
    private:
        virtual void update();

        void scrollLeft();
        void scrollRight();
        void scrollUp();
        void scrollDown();

    protected:
        int _scrollSpeed;
        int _scrollBorder;

    public:
        int const& scrollSpeed = _scrollSpeed;
        int const& scrollBorder = _scrollBorder;

        TAllroundScroller(TFrame* baseFrame /*!= 0*/,
                          unsigned orderIndex = DEFAULT_ORDER_INDEX,
                          int scrollSpeed = DEFAULT_SCROLL_SPEED,
                          int scrollBorder = DEFAULT_SCROLL_BORDER);
};

inline void TAllroundScroller::scrollLeft() {
    if (static_cast<TFrame*>(baseObject)->x < scrollSpeed)
        static_cast<TFrame*>(baseObject)->setX(0);
    else
        static_cast<TFrame*>(baseObject)->setX(static_cast<TFrame*>(baseObject)->x - scrollSpeed);
}

inline void TAllroundScroller::scrollRight() {
    if (static_cast<TFrame*>(baseObject)->x + scrollSpeed > static_cast<TFrame*>(baseObject)->boundRight)
        static_cast<TFrame*>(baseObject)->setX(static_cast<TFrame*>(baseObject)->boundRight);
    else
        static_cast<TFrame*>(baseObject)->setX(static_cast<TFrame*>(baseObject)->x + scrollSpeed);
}

inline void TAllroundScroller::scrollUp() {
    if (static_cast<TFrame*>(baseObject)->y < scrollSpeed)
        static_cast<TFrame*>(baseObject)->setY(0);
    else
        static_cast<TFrame*>(baseObject)->setY(static_cast<TFrame*>(baseObject)->y - scrollSpeed);
}

inline void TAllroundScroller::scrollDown() {
    if (static_cast<TFrame*>(baseObject)->y + scrollSpeed > static_cast<TFrame*>(baseObject)->boundBottom)
        static_cast<TFrame*>(baseObject)->setY(static_cast<TFrame*>(baseObject)->boundBottom);
    else
        static_cast<TFrame*>(baseObject)->setY(static_cast<TFrame*>(baseObject)->y + scrollSpeed);
}

}

#undef DEFAULT_ORDER_INDEX
#undef DEFAULT_SCROLL_SPEED
#undef DEFAULT_SCROLL_BORDER

#endif // KENG_OBJ_TYPES_DUMMY_HPP_INCLUDED
