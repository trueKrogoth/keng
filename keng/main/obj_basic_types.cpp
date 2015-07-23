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

TComponent::TComponent(
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
:   TComponent(
    0,
    base,
    orderIndex)
{
}

void TComponent::update() {
}

void TComponent::remove() {
    if (base != 0) {
        if (base->order_component[orderIndex] == this) {
            --iterator;
            if (static_cast<TComponent&>(*iterator).orderIndex == orderIndex)
                base->order_component[orderIndex] = &(static_cast<TComponent&>(*iterator));
            else
                base->order_component[orderIndex] = 0;
            ++iterator;
        }
        base->component_list.erase(++iterator);
    }
}

TComponent::~TComponent() {
}

//  ____________________
///[_______TBasis_______]

TBasis::TBasis(
    unsigned typeIndex,
    TBasis* base,
    unsigned orderIndex)
:   TComponent(
    typeIndex,
    base,
    orderIndex),
    order_component(15)
{
}

TBasis::TBasis(
    TBasis* base,
    unsigned orderIndex)
:   TBasis(
    0,
    base,
    orderIndex)
{
}

void TBasis::insert(TComponent* component) {
    for (int i = component->orderIndex; i != 0; --i)
        if (order_component[i] != 0) {
            std::list<TComponent>::iterator temp_iterator = order_component[i]->iterator;
            component->iterator = component_list.insert(++temp_iterator, *component);
            order_component[i] = component;
            return;
        }
    order_component[0] = component;
    component_list.push_front(*component);
    component->iterator = component_list.begin();
}

void TBasis::update() {
    for (TComponent& component : component_list)
        component.update();
}

void TBasis::remove() {
    component_list.clear();
    if (base != 0)
        base->component_list.erase(++iterator);
}

TBasis::~TBasis() {
}
