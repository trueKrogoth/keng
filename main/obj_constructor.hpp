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

#ifndef KENG_MAIN_OBJ_CONSTRUCTOR_HPP_INCLUDED
#define KENG_MAIN_OBJ_CONSTRUCTOR_HPP_INCLUDED

#include "obj_basic_types.hpp"

namespace Keng {

class __object_constructor_indexer {
    public:
        __object_constructor_indexer(int type_index, TObject*(*constructor)(CObject*, TObject*));
};

template<class T, class C> TObject* __object_constructor(CObject* config, TObject* baseObject) {
    return new T(static_cast<C*>(config), baseObject);
}

#define DEFINE_OBJECT_CONSTRUCTOR(type_index, T, C) \
__object_constructor_indexer type##_indexer_instance(type_index, &__object_constructor<T, C>); \
T::T(int typeIndex, CObject* config, TObject* baseObject) : TObject(type_index, config, baseObject = 0)

}

#endif // KENG_MAIN_OBJ_CONSTRUCTOR_HPP_INCLUDED
