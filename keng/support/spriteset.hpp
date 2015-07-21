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

#ifndef KENG_SUPPORT_SPRITESET_HPP_INCLUDED
#define KENG_SUPPORT_SPRITESET_HPP_INCLUDED

#include "dataset.hpp"
#include <gl/gl.h>

///>
#define SPRITES_PATH "sprites/"
///<

#define ANIMATION_TYPES_COUNT 1

class spritegroup_t {
    private:
        int _x;
        int _y;
        int _frames;
        bool _vertical;

    public:
        int const& x = _x;
        int const& y = _y;
        int const& frames = _frames;
        bool const& vertical = _vertical;

        spritegroup_t();
};

class spriteset_t : public dataset_t<spriteset_t> {
    private:
        GLuint _texture;
        int _textureWidth;
        int _textureHeight;

        int _spritesX;
        int _spritesY;

        int _spriteWidth;
        int _spriteHeight;
        GLfloat _spriteNormedWidth;
        GLfloat _spriteNormedHeight;

        spritegroup_t* _animationGroup[ANIMATION_TYPES_COUNT];

    public:
        GLuint const& texture = _texture;
        int const& textureWidth = _textureWidth;
        int const& textureHeight = _textureHeight;

        int const& spritesX = _spritesX;
        int const& spritesY = _spritesY;

        int const& spriteWidth = _spriteWidth;
        int const& spriteHeight = _spriteHeight;
        GLfloat const& spriteNormedWidth = _spriteNormedWidth;
        GLfloat const& spriteNormedHeight = _spriteNormedHeight;

        spritegroup_t* animationGroup(int type);

        spriteset_t(const char* filename);
};

typedef spriteset_t Spriteset;

#endif // KENG_SUPPORT_SPRITESET_HPP_INCLUDED
