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

#ifndef KENG_OBJ_TYPES_BASIS_HPP_INCLUDED
#define KENG_OBJ_TYPES_BASIS_HPP_INCLUDED

#include "component.hpp"
#include <list>
#include <vector>
#include "../main/obj_type_index.hpp"

#define TBASIS_INDEX UNIQUE_OBJ_TYPE_INDEX

namespace Keng {

//~~~~~~~~~~~~~~~~~
/// Tools
//~~~~~~~~~~~~~~~~~
class TBasis_tools {
    friend class TComponent;

    private:
        void insert(TComponent* component);
        void erase(TComponent* component);
};
//~~~~~~~~~~~~~~~~~
/// Main
//~~~~~~~~~~~~~~~~~
class TBasis:
    public TComponent,
    public TBasis_tools
{
    friend class TBasis_tools;

    public:
        TBasis(
            TBasis* base = 0,
            unsigned orderIndex = 0);

        virtual ~TBasis();

        virtual void update();
        virtual void remove();

    protected:
        TBasis(
            unsigned typeIndex,
            TBasis* base,
            unsigned orderIndex);

    private:
        std::list<TComponent> component_list;
        std::vector<TComponent*> back_component;

        void insert_impl(TComponent* component);
        void erase_impl(TComponent* component);
};

}

#endif // KENG_OBJ_TYPES_BASIS_HPP_INCLUDED
