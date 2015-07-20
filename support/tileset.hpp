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

#ifndef KENG_SUPPORT_TILESET_HPP_INCLUDED
#define KENG_SUPPORT_TILESET_HPP_INCLUDED

#include "spriteset.hpp"

///>
#define TILES_PATH "tiles/"
///<

class tileset_t {
    int _types;

    int _tileWidth;
    int _tileHeight;
    float _tileInverseWidth;
    float _tileInverseHeight;

    int _clipTilesX;
    int _clipTilesY;

    spriteset_t* _spriteset;

    public:
        int const& types = _types;

        int const& tileWidth = _tileWidth;
        int const& tileHeight = _tileHeight;
        float const& tileInverseWidth = _tileInverseWidth;
        float const& tileInverseHeight = _tileInverseHeight;

        int const& clipTilesX = _clipTilesX;
        int const& clipTilesY = _clipTilesY;

        spriteset_t* const& spriteset = _spriteset;

        tileset_t(const char* filename);
};

#endif // KENG_SUPPORT_TILESET_HPP_INCLUDED
