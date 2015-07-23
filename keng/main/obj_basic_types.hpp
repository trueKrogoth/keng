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

#ifndef KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
#define KENG_MAIN_BASIC_TYPES_HPP_INCLUDED

#include <list>
#include <vector>

namespace Keng {

//  ________________________
///[_______TComponent_______]

class TBasis;
class TComponent {
    friend class TBasis;

    private:
        std::list<TComponent>::iterator iterator;

        unsigned _typeIndex;
        TBasis* _base;
        unsigned _orderIndex;

    protected:
        TComponent(
            unsigned typeIndex,
            TBasis* base,
            unsigned orderIndex);

    public:
        TComponent(
            TBasis* base = 0,
            unsigned orderIndex = 0);

        unsigned const& typeIndex = _typeIndex;
        TBasis* const& base = _base;
        unsigned const& orderIndex = _orderIndex;

        virtual void update();

        virtual void remove();

        virtual ~TComponent();
};

//  ____________________
///[_______TBasis_______]

class TBasis : public TComponent {
    friend class TComponent;

    private:
        std::list<TComponent> component_list;
        std::vector<TComponent*> order_component;

        void insert(TComponent* component);

    protected:
        TBasis(
            unsigned typeIndex,
            TBasis* base,
            unsigned orderIndex);

    public:
        TBasis(
            TBasis* base = 0,
            unsigned orderIndex = 0);

        virtual void update();

        virtual void remove();

        virtual ~TBasis();
};

}

#endif // KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
