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
#include "../support/error.hpp"
#if SAFE_MODE
#include "obj_type_index.hpp"
#endif

using namespace Keng;

///TObject

TObject::TObject(int typeIndex, bool passFlag) {
#if SAFE_MODE
    if (typeIndex < 0) {
        ShowError("INPUT ERROR");
        _typeIndex = 0;
    }
    else
    if (typeIndex >= OBJECT_TYPE_COUNT) {
        ShowError("INPUT ERROR");
        _typeIndex = OBJECT_TYPE_COUNT - 1;
    }
    else
#endif
    _typeIndex = typeIndex;

    this->_passFlag = passFlag;
}

TObject::~TObject() {
    if (subObject != 0)
        subObject->loopDelete();
}

void TObject::loopUpdate() {
    update();
    if (subObject != 0)
        subObject->loopUpdate();
    if (nextObject->passFlag)
        nextObject->loopUpdate();
}

void TObject::loopDelete() {
    if (nextObject->passFlag)
        nextObject->loopDelete();
    delete this;
}

///TBasis

TBasis::TBasis(TObject* baseObject, int orderSize, int __typeIndex) : TObject(__typeIndex, false) {
    _prevObject = this;
    _nextObject = this;
    _subObject = 0;
    this->_baseObject = baseObject;
    if (baseObject != 0)
        baseObject->_subObject = this;

    _orderIndex = -1;

#if SAFE_MODE
    if (orderSize < 0) {
        ShowError("INPUT ERROR");
        _orderSize = orderSize;
    }
    else
#endif
    _orderSize = orderSize;

    orderComponent = new TComponent*[orderSize];
    for (int i = 0; i != orderSize; i++)
        orderComponent[i] = 0;
}

TBasis::~TBasis() {
}

void TBasis::remove() {
    if (baseObject != 0)
        baseObject->_subObject = 0;
    loopDelete();
}

TObject* TBasis::getPosition(int orderIndex) {
#if SAFE_MODE
    if (orderIndex >= orderSize) {
        ShowError("ERROR");
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

///TComponent

TComponent::TComponent(TObject * baseObject, int orderIndex, int __typeIndex) : TObject(__typeIndex, true) {
#if SAFE_MODE
    if (orderIndex < 0) {
        ShowError("INPUT ERROR");
        _orderIndex = 0;
    }
    else
#endif
    _orderIndex = orderIndex;

    this->_baseObject = baseObject;
#if SAFE_MODE
    if (baseObject == 0) {
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
            //^ component rudiment run-time advantage (no check whether the object is component)
            static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] = static_cast<TComponent*>(prevObject);
                //^ semantical explicitation compile-time disadvantage
        else
            static_cast<TBasis*>(baseObject)->orderComponent[orderIndex] = 0;
    }

    delete this;
}
