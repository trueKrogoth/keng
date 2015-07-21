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

        int _orderIndex; //little optimization rudiment

    public:
        int const& typeIndex = _typeIndex;

        bool const& passFlag = _passFlag;

        TObject* const& prevObject = _prevObject;
        TObject* const& nextObject = _nextObject;
        TObject* const& baseObject = _baseObject;
        TObject* const& subObject = _subObject;

        TObject(bool passFlag);
        inline void initTypeIndex(int typeIndex) {
            if (_typeIndex == -1)
                _typeIndex = typeIndex;
        #if SAFE_MODE
            else
                ShowError("ERROR");
        #endif
        };
        virtual ~TObject();

        virtual void remove() = 0;
};

///TBasis

class TComponent;
class TBasis : public TObject {
    friend class TObject;
    friend class TComponent;

    private:
        int _orderSize;

        TComponent* * orderComponent;

        TObject* getPosition(int orderIndex);

        virtual void update() = 0;

    public:
        int const& orderSize = _orderSize;

        TBasis(TObject* baseObject, int orderSize);
        virtual ~TBasis();

        inline void updateAll() {loopUpdate();};
        void remove();
};

///TComponent

class TComponent : public TObject {
    friend class TObject;
    friend class TBasis;

    private:
        //int _orderIndex;

        virtual void update() = 0;

    public:
        int const& orderIndex = _orderIndex;

        TComponent(TObject* baseObject /*!= 0*/, int orderIndex);
        virtual ~TComponent();

        void remove();
};

}

#endif // KENG_MAIN_BASIC_TYPES_HPP_INCLUDED
