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

#include "component.hpp"
#include "basis.hh"

using namespace Keng;

TComponent::TComponent(
    unsigned typeId,
    TBasis* base,
    unsigned position)
:   _typeId(typeId),
    _base(base),
    _position(position)
{
    if (base != 0)
        base->insert(this);
}

TComponent::TComponent(
    TBasis* base,
    unsigned position)
:   TComponent(
    TCOMPONENT,
    base,
    position)
{
}

TComponent::~TComponent() {
    if (base != 0)
        base->erase(this);
}

void TComponent::update() {
}
