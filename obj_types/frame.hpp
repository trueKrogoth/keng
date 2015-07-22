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

#define TFRAME_INDEX UNIQUE_OBJ_TYPE_INDEX

#define CFRAME_DEFS\
        TObject* baseObject = 0,\
        unsigned orderSize = 30,\
        int boundRight = 0,\
        int boundBottom = 0,\
        int startX = 0,\
        int startY = 0

#define CFRAME_ARGS\
        TObject* baseObject,\
        unsigned orderSize,\
        int boundRight,\
        int boundBottom,\
        int startX,\
        int startY

#define CFRAME_VALS\
        baseObject,\
        orderSize,\
        boundRight,\
        boundBottom,\
        startX,\
        startY

namespace Keng {

class TFrame : public TBasis {
    private:
        virtual void update();

    protected:
        int _boundRight;
        int _boundBottom;

        int _x;
        int _y;

        TFrame(IM_ARGS(CFRAME_ARGS));

    public:
        int const& boundRight = _boundRight;
        int const& boundBottom = _boundBottom;

        int const& x = _x;
        int const& y = _y;

        TFrame(CFRAME_DEFS);

        virtual void setX(int x);
        virtual void setY(int y);
};

inline TFrame::TFrame(IM_ARGS(CFRAME_ARGS)) : TBasis(IM_VALS(CBASIS_VALS)) {
    _boundRight = boundRight;
    _boundBottom = boundBottom;

    _x = startX;
    _y = startY;
};

inline TFrame::TFrame(CFRAME_ARGS) : TFrame(IM_VALS(CFRAME_VALS)) {
};

inline void TFrame::update() {
}

inline void TFrame::setX(int x) {
    _x = x;
}

inline void TFrame::setY(int y) {
    _y = y;
}

}

#endif // KENG_OBJ_TYPES_FRAME_HPP_INCLUDED
