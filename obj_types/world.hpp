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

#define DEFS\
        TObject* baseObject = 0,\
        unsigned orderSize = 30,\
        int boundRight = 0,\
        int boundBottom = 0,\
        int startX = 0,\
        int startY = 0

#define ARGS\
        TObject* baseObject,\
        unsigned orderSize,\
        int boundRight,\
        int boundBottom,\
        int startX,\
        int startY

#define VALS\
        baseObject,\
        orderSize,\
        boundRight,\
        boundBottom,\
        startX,\
        startY

#define TWORLD_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CWORLD_VALS VALS
#define BWORLD static_cast<TWorld*>(baseObject)

namespace Keng {

class TWorld : public TFrame {
    private:
        virtual void update();

    protected:
        TTilebox* _tilebox;

        TWorld(IM_ARGS(ARGS));

    public:
        TTilebox* const& tilebox = _tilebox;

        TWorld(DEFS);

        void setTilebox(TTilebox* tilebox);

        virtual void setX(int x);
        virtual void setY(int y);
};

inline TWorld::TWorld(IM_ARGS(ARGS)) : TFrame(IM_VALS(CFRAME_VALS)) {
    _tilebox = 0;
}

inline TWorld::TWorld(ARGS) : TWorld(IM_VALS(VALS)) {
}

inline void TWorld::update() {
}

inline void TWorld::setTilebox(TTilebox* tilebox) {
    _tilebox = tilebox;

    _boundRight = tilebox->tilesX * tilebox->tileset->tileWidth - Prog::displayWidth;
    if (boundRight < 0)
        _boundRight = 0;
    _boundBottom = tilebox->tilesY * tilebox->tileset->tileHeight - Prog::displayHeight;
    if (boundBottom < 0)
        _boundBottom = 0;
}

void TWorld::setX(int x) {
    if (x < 0)
        _x = 0;
    else
    if (x > boundRight)
        _x = boundRight;
    else
        _x = x;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipX();
}

void TWorld::setY(int y) {
    if (y < 0)
        _y = 0;
    else
    if (y > boundBottom)
        _y = boundBottom;
    else
        _y = y;
#if SAFE_MODE
    if (tilebox != 0)
#endif
    tilebox->updateClipY();
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_WORLD_HPP_INCLUDED
