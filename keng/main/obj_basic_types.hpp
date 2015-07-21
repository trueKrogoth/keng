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

///TObject

class TObject {
    friend class TBasis;
    friend class TComponent;

    private:
        int _typeIndex;

        bool _passFlag;

        TObject* _prevObject;
        TObject* _nextObject;
        TObject* _baseObject;
        TObject* _subObject;

        void loopUpdate();
        void loopDelete();

        virtual void update() = 0;

        unsigned _orderIndex; //little optimization rudiment

    public:
        int const& typeIndex = _typeIndex;

        bool const& passFlag = _passFlag;

        TObject* const& prevObject = _prevObject;
        TObject* const& nextObject = _nextObject;
        TObject* const& baseObject = _baseObject;
        TObject* const& subObject = _subObject;

        TObject(bool passFlag);
        void initTypeIndex(int typeIndex);
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

inline void TObject::initTypeIndex(int typeIndex) {
    if (_typeIndex == -1)
        _typeIndex = typeIndex;
#if SAFE_MODE
    else
        ShowMessage("WARNING! Tried to change object type index.");
#endif
}

///TBasis

class TComponent;
class TBasis : public TObject {
    friend class TObject;
    friend class TComponent;

    private:
        unsigned _orderSize;

        TComponent* * orderComponent;

        TObject* getPosition(unsigned orderIndex);

        virtual void update() = 0;

    public:
        unsigned const& orderSize = _orderSize;

        TBasis(TObject* baseObject, unsigned orderSize);
        virtual ~TBasis();

        void updateAll();
        void remove();
};

inline void TBasis::updateAll() {
    loopUpdate();
}

///TComponent

class TComponent : public TObject {
    friend class TObject;
    friend class TBasis;

    private:
        //unsigned _orderIndex;

        virtual void update() = 0;

    public:
        unsigned const& orderIndex = _orderIndex;

        TComponent(TObject* baseObject /*!= 0*/, unsigned orderIndex);
        virtual ~TComponent();

        void remove();
};

}

#endif // KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
