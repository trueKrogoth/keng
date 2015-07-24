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

using namespace Keng;

///void TBasis_tools::insert(TComponent* component) {...} - basis.hh

///void TBasis_tools::erase(TComponent* component) {...} - basis.hh

TBasis::TBasis(
    unsigned typeIndex,
    TBasis* base,
    unsigned orderIndex)
:   TComponent(
    typeIndex,
    base,
    orderIndex),
    back_component(15)
{
}

TBasis::TBasis(
    TBasis* base,
    unsigned orderIndex)
:   TBasis(
    TBASIS_INDEX,
    base,
    orderIndex)
{
}

TBasis::~TBasis() {
}

void TBasis::update() {
    for (TComponent& component : component_list)
        component.update();
}

void TBasis::remove() {
    component_list.clear();
    TComponent::remove();
}

///void TBasis::insert_impl(TComponent* component) {...} - basis.hh

///void TBasis::erase_impl(TComponent* component) {...} - basis.hh
