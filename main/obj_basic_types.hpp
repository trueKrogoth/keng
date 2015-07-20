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

namespace Keng {

///CObject, TObject

class CObject {
    private:
        int _typeIndex;

    public:
        int const& typeIndex = _typeIndex;

        CObject(int configIndex, int typeIndex);
};

class TObject {
    private:
        int _typeIndex;

    protected:
        int const& typeIndex = _typeIndex;
//-----------------
    friend class TBasis;
    friend class TComponent;
    friend void LoopUpdate(TObject*); //obj_interface.hpp

    private:
        bool passFlag;

        TObject* prevObject;
        TObject* nextObject;
        TObject* baseObject;
        TObject* subObject;

        void loopUpdate();
        void loopDelete();

        virtual void update() = 0;

        int _orderIndex; //performance rudiment

    public:
        virtual ~TObject();
};

///CBasis, TBasis

class CBasis : public CObject {
    private:
        int _orderSize;

    public:
        int const& orderSize = _orderSize;

        CBasis(int configIndex, int typeIndex, int orderSize);
};

class TComponent;
class TBasis : public TObject {
    private:
        int _orderSize;

    public:
        int const& orderSize = _orderSize;
//-----------------
    friend class TObject;
    friend class TComponent;

    private:
        TComponent* * orderComponent; //semantical explicitation

        TObject* getPosition(int orderIndex);

        virtual void update() = 0;

    public:
        TBasis(int typeIndex, CBasis* config, TObject* baseObject);
        virtual ~TBasis();
        void destroy();
};

///CComponent, TComponent

class CComponent : public CObject {
    private:
        int _orderIndex;

    public:
        int const& orderIndex = _orderIndex;

        CComponent(int configIndex, int typeIndex, int orderIndex);
};

class TComponent : public TObject {
    private:
        //int _orderIndex;

    protected:
        int const& orderIndex = _orderIndex;
//-----------------
    friend class TObject;
    friend class TBasis;

    private:
        virtual void update() = 0;

    protected:
        TBasis* const& basis = static_cast<TBasis*>(baseObject);

    public:
        TComponent(int typeIndex, CComponent* config, TObject* baseObject);
        virtual ~TComponent();
        void destroy();
};

}

#endif // KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
