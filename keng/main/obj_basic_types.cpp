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
#include "obj_type_index.hpp"

using namespace Keng;

//  _____________________
///[_______TObject_______]

TObject::TObject(unsigned typeIndex, bool passFlag) : _typeIndex(typeIndex), _passFlag(passFlag) {
}

TObject::~TObject() {
    if (subObject != 0)
        subObject->loopDelete();
}

//  ____________________
///[_______TBasis_______]

TBasis::TBasis(bool __dummy, unsigned __typeIndex, TObject* baseObject, unsigned orderSize) : TObject(__typeIndex, false) {
    _prevObject = this;
    _nextObject = this;
    _subObject = 0;
    _baseObject = baseObject;
    if (baseObject != 0)
        baseObject->_subObject = this;

    _orderIndex = -1;

    _orderSize = orderSize;

    orderComponent = new TComponent*[orderSize];
    for (unsigned i = 0; i != orderSize; i++)
        orderComponent[i] = 0;
}

TBasis::~TBasis() {
}

void TBasis::remove() {
    if (baseObject != 0)
        baseObject->_subObject = 0;
    loopDelete();
}

TObject* TBasis::getPosition(unsigned orderIndex) {
#if SAFE_MODE
    if (orderIndex >= orderSize) {
        ShowMessage("ERROR! An object has too large order index.");
        orderIndex = orderSize - 1;
    }
#endif
    while (orderComponent[orderIndex] == 0) {
        if (orderIndex == 0)
            return this;
        orderIndex--;
    }
    return orderComponent[orderIndex];
}

//  ________________________
///[_______TComponent_______]

TComponent::TComponent(bool __dummy, unsigned __typeIndex, TObject * baseObject, unsigned orderIndex) : TObject(__typeIndex, true) {
    _orderIndex = orderIndex;

    _baseObject = baseObject;
#if SAFE_MODE
    if (baseObject == 0) {
        ShowMessage("WARNING! Created a component at no basis.");
        _prevObject = this;
        _nextObject = this;
    }
    else
#endif
    {
        _prevObject = static_cast<TBasis*>(baseObject)->getPosition(orderIndex);
        static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] = this;
        _nextObject = prevObject->nextObject;
        prevObject->_nextObject = this;
        nextObject->_prevObject = this;
    }
    _subObject = 0;
}

TComponent::~TComponent() {
}

void TComponent::remove() {
    prevObject->_nextObject = nextObject;
    nextObject->_prevObject = prevObject;

#if SAFE_MODE
    if (baseObject != 0)
#endif
    if (static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] == this) {
        if (prevObject->_orderIndex == orderIndex)
            static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] = static_cast<TComponent*>(prevObject);
        else
            static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] = 0;
    }

    delete this;
}
