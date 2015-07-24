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

void TBasis_tools::insert(TComponent* component) {
    static_cast<TBasis*>(this)->insert_impl(component);
}

void TBasis_tools::erase(TComponent* component) {
    static_cast<TBasis*>(this)->erase_impl(component);
}

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

void TBasis::insert_impl(TComponent* component) {
    if (component->orderIndex >= back_component.size())
        back_component.resize(component->orderIndex + 1);
    for (int i = component->orderIndex; i != -1; --i)
        if (back_component[i] != 0) {
            std::list<TComponent>::iterator temp_iterator = back_component[i]->iterator;
            component->iterator = component_list.insert(++temp_iterator, *component);
            back_component[i] = component;
            return;
        }
    back_component[0] = component;
    component_list.push_front(*component);
    component->iterator = component_list.begin();
}

void TBasis::erase_impl(TComponent* component) {
    if (back_component[component->orderIndex] == component) {
        --component->iterator;
        if (static_cast<TComponent&>(*component->iterator).orderIndex == component->orderIndex)
            back_component[component->orderIndex] = &(static_cast<TComponent&>(*component->iterator));
        else
            back_component[component->orderIndex] = 0;
        ++component->iterator;
    }
    component_list.erase(++component->iterator);
}
