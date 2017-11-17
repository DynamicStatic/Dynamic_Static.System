
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Object.hpp"

namespace Dynamic_Static {
namespace System {

    Object::Object()
    {
        set_name("System::Object");
    }

    Object::Object(Object && other)
    {
        *this = std::move(other);
    }

    Object::~Object()
    {
    }

    Object& Object::operator=(Object&& other)
    {
        if (this != &other) {
            dst::Object::operator=(std::move(other));
        }

        return *this;
    }

} // namespace System
} // namespace Dynamic_Static
