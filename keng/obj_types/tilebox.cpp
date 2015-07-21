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

#include "tilebox.hpp"
#include "../main/prog.hpp"
#include "../support/graphics.hpp"
#include "../support/error.hpp"

using namespace Keng;

TTilebox::TTilebox(TFrame* baseFrame, unsigned orderIndex,
                   tileset_t* tileset, unsigned tilesX, unsigned tilesY) :
                   TComponent(baseFrame, orderIndex)
               #if SAFE_MODE
                 , _tile(0)
               #endif
                 { initTypeIndex(OBJECT_TYPE_TILEBOX);
    _tileset = tileset;

    _tilesX = tilesX;
    _tilesY = tilesY;

#if SAFE_MODE
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

void TTilebox::generate() {
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

void TTilebox::update() {
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    TFrame* frame = (TFrame*)(baseObject);
    leftClip = 0;
    glTranslatef(static_cast<int>(leftClip) * tileset->tileWidth - static_cast<TFrame*>(baseObject)->x,
                 static_cast<int>(topClip) * tileset->tileHeight - static_cast<TFrame*>(baseObject)->y, .0f);
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
