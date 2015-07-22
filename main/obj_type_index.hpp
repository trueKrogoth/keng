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

#ifndef KENG_MAIN_TYPE_INDEX_HPP_INCLUDED
#define KENG_MAIN_TYPE_INDEX_HPP_INCLUDED

    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/slot/slot.hpp>

    #define BOOST_PP_VALUE 0
    #include BOOST_PP_ASSIGN_SLOT(1)
    #undef BOOST_PP_VALUE

    #define UNIQUE_OBJ_TYPE_INDEX BOOST_PP_SLOT(1)
    #define OBJ_TYPE_COUNT BOOST_PP_SLOT(1)

#else

    #define BOOST_PP_VALUE BOOST_PP_INC(BOOST_PP_SLOT(1))
    #include BOOST_PP_ASSIGN_SLOT(1)
    #undef BOOST_PP_VALUE

#endif
