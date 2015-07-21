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

#include "cursor.hpp"
#include "../main/prog.hpp"

using namespace Keng;

TCursor::TCursor(TFrame* baseFrame, int orderIndex) :
                 TComponent(baseFrame, orderIndex) {
                 initTypeIndex(OBJECT_TYPE_FRAME);
    sprite = new TSprite(static_cast<TFrame*>(baseFrame), 1, new spriteset_t("cursor.spr"));
}

void TCursor::update() {
    sprite->setCoords(Prog::mouseX, Prog::mouseY);
}
