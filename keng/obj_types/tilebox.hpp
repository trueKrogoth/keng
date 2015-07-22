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
#include "../support/graphics.hpp"

#define DEFS\
        TFrame* baseObject,\
        unsigned orderIndex = 0,\
        tileset_t* tileset = Tileset::file("barrens.tls"),\
        unsigned tilesX = 100,\
        unsigned tilesY = 100

#define ARGS\
        TFrame* baseObject,\
        unsigned orderIndex,\
        tileset_t* tileset,\
        unsigned tilesX,\
        unsigned tilesY

#define VALS\
        baseObject,\
        orderIndex,\
        tileset,\
        tilesX,\
        tilesY

#define TTILEBOX_INDEX UNIQUE_OBJ_TYPE_INDEX
#define CTILEBOX_VALS VALS

namespace Keng {

class TTilebox : public TComponent {
    private:
        tileset_t* _tileset;

        unsigned _tilesX;
        unsigned _tilesY;

        unsigned ** _tile;

        unsigned leftClip;
        unsigned rightClip;
        unsigned topClip;
        unsigned bottomClip;

        virtual void update();

    protected:
        TTilebox(IM_ARGS(ARGS));

    public:
        tileset_t* const& tileset = _tileset;

        unsigned const& tilesX = _tilesX;
        unsigned const& tilesY = _tilesY;

        unsigned ** const& tile = _tile;

        TTilebox(DEFS);

        void generate();

        void updateClipX();
        void updateClipY();
};

inline TTilebox::TTilebox(IM_ARGS(ARGS)) : TComponent(IM_VALS(CCOMPONENT_VALS)) {
    _tileset = tileset;

    _tilesX = tilesX;
    _tilesY = tilesY;

#if SAFE_MODE
    _tile = 0;

    if (tileset == 0)
        ShowMessage("WARNING! Created tilebox with no tileset.");
    else
#endif
    {
        updateClipX();
        updateClipY();
    }

#if SAFE_MODE
    generate();
#endif
}

inline TTilebox::TTilebox(ARGS) : TTilebox(IM_VALS(VALS)) {
}

inline void TTilebox::update() {
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(static_cast<int>(leftClip) * tileset->tileWidth - BFRAME->x,
                 static_cast<int>(topClip) * tileset->tileHeight - BFRAME->y, .0f);
    for (unsigned i = topClip; i != bottomClip; i++) {
        glPushMatrix();
        for (unsigned j = leftClip; j != rightClip; j++) {
            DrawSprite(tileset->spriteset, tile[i][j]);
            glTranslatef(tileset->tileWidth, .0f, .0f);
        }
        glPopMatrix();
        glTranslatef(.0f, tileset->tileHeight, .0f);
    }
}

inline void TTilebox::generate() {
    if (tile != 0) {
        for (unsigned i = 0; i != tilesY; i++)
            delete[] tile[i];
        delete[] tile;
    }
    _tile = new unsigned *[tilesY];
    for (unsigned i = 0; i != tilesY; i++) {
        _tile[i] = new unsigned[tilesX];
        for (unsigned j = 0; j != tilesX; j++)
            _tile[i][j] = rand() % tileset->types;
    }
}

inline void TTilebox::updateClipX() {
    leftClip = BFRAME->x * tileset->tileInverseWidth;
    rightClip = leftClip + tileset->clipTilesX;
    if (rightClip > tilesX)
        rightClip = tilesX;
}

inline void TTilebox::updateClipY() {
    topClip = BFRAME->y * tileset->tileInverseHeight;
    bottomClip = topClip + tileset->clipTilesY;
    if (bottomClip > tilesY)
        bottomClip = tilesY;
}

}

#undef DEFS
#undef ARGS
#undef VALS

#endif // KENG_OBJ_TYPES_TILEBOX_HPP_INCLUDED
