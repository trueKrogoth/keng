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

#ifndef KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED
#define KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED

#include "basis.hpp"
#include "../main/obj_type_id.hh"

#define TBACKGROUND UNIQUE_OBJ_TYPE_ID

namespace Keng {

//~~~~~~~~~~~~~~~~~
/// Main
//~~~~~~~~~~~~~~~~~
class TBackground :
    public TComponent
{
    public:
        TBackground(
            TBasis* base = 0,
            unsigned position = 0);

        void update();

    protected:
        TBackground(
            unsigned typeId,
            TBasis* base,
            unsigned position);
};

}

#endif // KENG_OBJ_TYPES_BACKGROUND_HPP_INCLUDED
