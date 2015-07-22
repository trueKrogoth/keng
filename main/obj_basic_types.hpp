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

#include "../support/error.hpp"

namespace Keng {

//  _____________________
///[_______TObject_______]

class TObject {
    friend class TBasis;
    friend class TComponent;

    private:
        unsigned _typeIndex;

        bool _passFlag;

        TObject* _prevObject;
        TObject* _nextObject;
        TObject* _baseObject;
        TObject* _subObject;

        void loopUpdate();
        void loopDelete();

        virtual void update() = 0;

        unsigned _orderIndex; //little optimization rudiment

    protected:
        TObject(unsigned typeIndex, bool passFlag);

    public:
        unsigned const& typeIndex = _typeIndex;

        bool const& passFlag = _passFlag;

        TObject* const& prevObject = _prevObject;
        TObject* const& nextObject = _nextObject;
        TObject* const& baseObject = _baseObject;
        TObject* const& subObject = _subObject;

        virtual ~TObject();

        virtual void remove() = 0;
};

inline void TObject::loopUpdate() {
    update();
    if (subObject != 0)
        subObject->loopUpdate();
    if (nextObject->passFlag)
        nextObject->loopUpdate();
}

inline void TObject::loopDelete() {
    if (nextObject->passFlag)
        nextObject->loopDelete();
    delete this;
}

//  ____________________
///[_______TBasis_______]

class TComponent;
class TBasis : public TObject {
    friend class TObject;
    friend class TComponent;

    private:
        unsigned _orderSize;

        TComponent* * orderComponent;

        TObject* getPosition(unsigned orderIndex);

        virtual void update() = 0;

    protected:
        TBasis(int dummy, unsigned typeIndex, TObject* baseObject, unsigned orderSize);

    public:
        unsigned const& orderSize = _orderSize;

        virtual ~TBasis();

        void updateAll();
        void remove();
};

inline void TBasis::updateAll() {
    loopUpdate();
}

#define CBASIS_VALS\
        baseObject,\
        orderSize

//  ________________________
///[_______TComponent_______]

class TComponent : public TObject {
    friend class TObject;
    friend class TBasis;

    private:
        //unsigned _orderIndex;

        virtual void update() = 0;

    protected:
        TComponent(int dummy, unsigned typeIndex, TObject* baseObject/*!= 0*/, unsigned orderIndex);

    public:
        unsigned const& orderIndex = _orderIndex;

        virtual ~TComponent();

        void remove();
};

#define CCOMPONENT_VALS\
        baseObject,\
        orderIndex

//  ______________________________
///[_______IM_ARGS,_IM_VALS_______]

#define IM_ARGS(ARGS)\
        int dummy,\
        unsigned typeIndex,\
        ARGS

#define IM_VALS(VALS)\
        0,\
        UNIQUE_OBJ_TYPE_INDEX,\
        VALS

}

#endif // KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
