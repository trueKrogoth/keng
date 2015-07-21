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

#ifndef KENG_SUPPORT_DATASET_HPP_INCLUDED
#define KENG_SUPPORT_DATASET_HPP_INCLUDED

#include <map>
#include <string>

template<class T>
class dataset_t {
    private:
        static std::map<std::string, void*> _map;

    public:
        static inline T* file(const char* filename);
};

template<class T>
std::map<std::string, void*> dataset_t<T>::_map;

template<class T>
T* dataset_t<T>::file(const char* filename) {
    std::map<std::string, void*>::const_iterator dataset = _map.find(filename);
    if (dataset == _map.end())
        return new T(filename);
    else
        return static_cast<T*>(dataset->second);
}

template<class T>
using Dataset = dataset_t<T>;

#endif // KENG_SUPPORT_DATASET_HPP_INCLUDED
