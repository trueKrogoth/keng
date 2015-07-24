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

#ifndef KENG_OBJ_TYPES_BASIS_HH_INCLUDED
#define KENG_OBJ_TYPES_BASIS_HH_INCLUDED

#include "basis.hpp"

namespace Keng {

inline void TBasis::insert_impl(TComponent* component) {
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

inline void TBasis::erase_impl(TComponent* component) {
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

inline void TBasis_tools::insert(TComponent* component) {
    static_cast<TBasis*>(this)->insert_impl(component);
}

inline void TBasis_tools::erase(TComponent* component) {
    static_cast<TBasis*>(this)->erase_impl(component);
}

}

#endif // KENG_OBJ_TYPES_BASIS_HH_INCLUDED
