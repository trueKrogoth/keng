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

#include "obj_basic_types.hpp"

using namespace Keng;

//  ________________________
///[_______TComponent_______]

TComponent::TComponent(bool __dummy,
    unsigned typeIndex,
    TBasis* base,
    unsigned orderIndex)
:   _typeIndex(typeIndex),
    _base(base),
    _orderIndex(orderIndex)
{
    if (base != 0) {
        if (orderIndex >= base->order_component.size())
            base->order_component.resize(orderIndex + 1);
        base->insert(this);
    }
}

TComponent::TComponent(
    TBasis* base,
    unsigned orderIndex)
:   TComponent(false, 0,
    base,
    orderIndex)
{
}

TComponent::~TComponent() {
}

void TComponent::update() {
}

void TComponent::remove() {
    if (base != 0) {
        if (base->order_component[orderIndex] == this) {
            if (static_cast<TComponent&>(*--iterator).orderIndex == orderIndex)
                base->order_component[orderIndex] = &(static_cast<TComponent&>(*iterator++));
            else
                base->order_component[orderIndex] = 0;
        }
        base->component_list.erase(++iterator);
    }
}

//  ____________________
///[_______TBasis_______]

TBasis::TBasis(bool __dummy,
    unsigned typeIndex,
    TBasis* base,
    unsigned orderIndex)
:   TComponent(__dummy,
    typeIndex,
    base,
    orderIndex),
    order_component(15)
{
}

TBasis::TBasis(
    TBasis* base,
    unsigned orderIndex)
:   TBasis(false, 0,
    base,
    orderIndex)
{
}

TBasis::~TBasis() {
}

void TBasis::insert(TComponent* component) {
    for (int i = component->orderIndex; i != 0; i--)
        if (order_component[i] != 0) {
            component->iterator = component_list.insert(++order_component[i]->iterator--, *component);
            order_component[i] = component;
            return;
        }
    order_component[0] = component;
    component_list.push_front(*component);
    component->iterator = component_list.begin();
}

void TBasis::update() {
    for (std::list<TComponent>::iterator i = component_list.begin(); i != component_list.end(); i++)
        i->update();
}

void TBasis::remove() {
    component_list.clear();
    if (base != 0)
        base->component_list.erase(++iterator);
}
