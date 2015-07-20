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

#include <fstream>
#include "spriteset.hpp"
#include "SOIL.h"

///Spritegroup

spritegroup_t::spritegroup_t() {
    _x = 0;
    _y = 0;
    _frames = 1;
    _vertical = true;
}

///Spriteset

spritegroup_t* spriteset_t::animationGroup(int type) {
    return _animationGroup[type];
}

spriteset_t::spriteset_t(const char* filename) {
    std::string filepath_str = filename;
    filepath_str = SPRITES_PATH + filepath_str;
    std::string texture_filepath_str;

    std::ifstream file;
    file.open(filepath_str.c_str());
    file >> texture_filepath_str;
    file >> _spritesX;
    file >> _spritesY;
    file.close();

    texture_filepath_str = SPRITES_PATH + texture_filepath_str;

    _texture =
        SOIL_load_OGL_texture(
            texture_filepath_str.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_POWER_OF_TWO
            | SOIL_FLAG_MIPMAPS
            | SOIL_FLAG_MULTIPLY_ALPHA
            | SOIL_FLAG_COMPRESS_TO_DXT
            | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_NTSC_SAFE_RGB
            );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &_textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &_textureHeight);
    glDisable(GL_TEXTURE_2D);

    _spriteNormedWidth = 1.0f / spritesX;
    _spriteNormedHeight = 1.0f / spritesY;
    _spriteWidth = spriteNormedWidth * textureWidth;
    _spriteHeight = spriteNormedHeight * textureHeight;

    for (int i = 0; i != ANIMATION_TYPES_COUNT; i++)
        _animationGroup[i] = new spritegroup_t();
}
