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
#include "obj_interface.hpp"

using namespace Keng;

///CObject, TObject

CObject::CObject(int configIndex, int typeIndex) {
#if CHECK_INPUT
    if (configIndex < 0) {
        ShowError("INPUT ERROR");
        ObjectIndexedData::config[0] = this;
    }
    else
    if (configIndex >= OBJECT_CONFIG_MAX_COUNT) {
        ShowError("INPUT ERROR");
        ObjectIndexedData::config[OBJECT_CONFIG_MAX_COUNT - 1] = this;
    }
    else
#endif
    ObjectIndexedData::config[configIndex] = this;

#if CHECK_INPUT
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

///CBasis, TBasis

CBasis::CBasis(int configIndex, int typeIndex, int orderSize) : CObject(configIndex, typeIndex) {
#if CHECK_INPUT
    if (orderSize < 0) {
        ShowError("INPUT ERROR");
        _orderSize = orderSize;
    }
    else
#endif
    _orderSize = orderSize;
}

TBasis::TBasis(int typeIndex, CBasis* config, TObject* baseObject) : TObject() {
    passFlag = false;

    prevObject = this;
    nextObject = this;
    subObject = 0;
    this->baseObject = baseObject;
    if (baseObject != 0)
        baseObject->subObject = this;

    _orderIndex = -1;

    _typeIndex = typeIndex;

    _orderSize = config->orderSize;

    orderComponent = new TComponent*[orderSize];
    for (int i = 0; i != orderSize; i++)
        orderComponent[i] = 0;
}

TBasis::~TBasis() {
}

void TBasis::destroy() {
    if (baseObject != 0)
        baseObject->subObject = 0;
    loopDelete();
}

TObject* TBasis::getPosition(int orderIndex) {
#if CHECK_INPUT
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

///CComponent, TComponent

CComponent::CComponent(int configIndex, int typeIndex, int orderIndex) : CObject(configIndex, typeIndex) {
#if CHECK_INPUT
    if (orderIndex < 0) {
        ShowError("INPUT ERROR");
        _orderIndex = 0;
    }
    else
#endif
    _orderIndex = orderIndex;
}

TComponent::TComponent(int typeIndex, CComponent * config, TObject * baseObject) : TObject() {
    passFlag = true;

    _typeIndex = typeIndex;

    _orderIndex = config->orderIndex;

    this->baseObject = baseObject;
    if (baseObject == 0) {
        prevObject = this;
        nextObject = this;
    }
    else {
        prevObject = basis->getPosition(orderIndex);
        basis->orderComponent[orderIndex] = this;
        nextObject = prevObject->nextObject;
        prevObject->nextObject = this;
        nextObject->prevObject = this;
    }
    subObject = 0;
}

TComponent::~TComponent() {
}

void TComponent::destroy() {
    prevObject->nextObject = nextObject;
    nextObject->prevObject = prevObject;

    if (basis->orderComponent[orderIndex] == this) {
        if (prevObject->_orderIndex == orderIndex)
            //^ component rudiment run-time advantage (no check if the object is component)
            basis->orderComponent[orderIndex] = static_cast<TComponent*>(prevObject);
                //^ semantical explicitation compile-time disadvantage
        else
            basis->orderComponent[orderIndex] = 0;
    }

    delete this;
}
