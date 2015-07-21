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

#include "graphics.hpp"

void DrawSprite(spriteset_t* spriteset, int column, int row, GLfloat scale, bool mirrorX, bool mirrorY) {
    GLfloat texture_x1 = spriteset->spriteNormedWidth * column;
    GLfloat texture_x2 = texture_x1 + spriteset->spriteNormedWidth;
    GLfloat texture_y1 = spriteset->spriteNormedHeight * row;
    GLfloat texture_y2 = texture_y1 + spriteset->spriteNormedHeight;
    int vertex_x1, vertex_x2, vertex_y1, vertex_y2;
    if (mirrorX) {
        vertex_x1 = spriteset->spriteWidth;
        vertex_x2 = 0;
    }
    else {
        vertex_x1 = 0;
        vertex_x2 = spriteset->spriteWidth;
    }
    if (mirrorY) {
        vertex_y1 = spriteset->spriteHeight;
        vertex_y2 = 0;
    }
    else {
        vertex_y1 = 0;
        vertex_y2 = spriteset->spriteHeight;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteset->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_POLYGON);
        glTexCoord2f(texture_x1, texture_y1);
        glVertex2f(vertex_x1, vertex_y1);
        glTexCoord2f(texture_x1, texture_y2);
        glVertex2f(vertex_x1, vertex_y2);
        glTexCoord2f(texture_x2, texture_y2);
        glVertex2f(vertex_x2, vertex_y2);
        glTexCoord2f(texture_x2, texture_y1);
        glVertex2f(vertex_x2, vertex_y1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
