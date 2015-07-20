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

#ifndef KENG_MAIN_OBJ_INTERFACE_HPP_INCLUDED
#define KENG_MAIN_OBJ_INTERFACE_HPP_INCLUDED

#include "obj_basic_types.hpp"
#include "../obj_type_ids.hpp"
#include "../obj_cfgs.hpp"
#include "../support/error.hpp"

namespace Keng {

///ObjectIndexedData

class ObjectIndexedData {
    friend class __object_constructor_indexer; //obj_constructor.hpp
    friend TObject* CreateObject(int, int, TObject*); //obj_interface.hpp
    friend class CObject;

    static TObject*(*constructor[OBJECT_TYPE_COUNT])(CObject*, TObject*);
    static CObject* config[OBJECT_CONFIG_MAX_COUNT];
};

///LoopUpdate

inline void LoopUpdate(TObject* object) {
#if CHECK_INPUT
    if (object == 0)
        ShowError("INPUT ERROR");
    else
#endif
    object->loopUpdate();
};

///CreateObject

inline TObject* CreateObject(int typeIndex, int configIndex, TObject* baseObject) {
#if CHECK_INPUT
    if (configIndex < 0 || configIndex >= OBJECT_CONFIG_MAX_COUNT ||
        ObjectIndexedData::config[configIndex] == 0 ||
        ObjectIndexedData::config[configIndex]->typeIndex != typeIndex) {
            ShowError("INPUT ERROR");
            return 0;
        }
#endif
    return (*ObjectIndexedData::constructor[typeIndex])(ObjectIndexedData::config[configIndex], baseObject);
};

}

#endif // KENG_MAIN_OBJ_INTERFACE_HPP_INCLUDED
