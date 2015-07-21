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

#include "tileset.hpp"
#include <fstream>
#include "../main/prog.hpp"

using namespace Keng;

tileset_t::tileset_t(const char* filename) {
    std::string filepath_str = filename;
    filepath_str = TILES_PATH + filepath_str;
    std::string sprite_filename_str;

    std::ifstream file;
    file.open(filepath_str.c_str());
    file >> sprite_filename_str;
    file.close();

    _spriteset = new spriteset_t(sprite_filename_str.c_str());

    _types = spriteset->spritesX * spriteset->spritesY;

    _tileWidth = spriteset->spriteWidth;
    _tileHeight = spriteset->spriteHeight;
    _tileInverseWidth = 1.0f / tileWidth;
    _tileInverseHeight = 1.0f / tileHeight;

    _clipTilesX = Prog::displayWidth * tileInverseWidth + 2;
    _clipTilesY = Prog::displayHeight * tileInverseHeight + 1;
}
