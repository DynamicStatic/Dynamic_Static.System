
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static.core.hpp"

struct Ray final
{
    glm::vec3 point_at_parameter(float t) const
    {
        return origin + direction * t;
    }

    glm::vec3 origin;
    glm::vec3 direction;
};
