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

#include "basis.hpp"

#include "background.hpp"

using namespace Keng;

///void TBasis_tools::insert(TComponent* component) {...} - basis.hh

///void TBasis_tools::erase(TComponent* component) {...} - basis.hh

TBasis::TBasis(
    unsigned typeId,
    TBasis* base,
    unsigned position)
:   TComponent(
    typeId,
    base,
    position),
    back_component(15)
{
}

TBasis::TBasis(
    TBasis* base,
    unsigned position)
:   TBasis(
    TBASIS,
    base,
    position)
{
}

TBasis::~TBasis() {
    for (TComponent*& component : component_list)
        delete component;
}

void TBasis::update() {
    for (TComponent*& component : component_list)
        component->update();
}

///void TBasis::insert_impl(TComponent* component) {...} - basis.hh

///void TBasis::erase_impl(TComponent* component) {...} - basis.hh
