
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "ray.hpp"

#include "dynamic_static.core.hpp"

class Camera final
{
public:
    inline Ray ray(const glm::vec2& texCoord) const
    {
        return { origin, lowerLeftCorner + texCoord.x * horizontal + texCoord.y * vertical - origin };
    }

    glm::vec3 origin { };
    glm::vec3 lowerLeftCorner { -2, -1, -1 };
    glm::vec3 horizontal { 4, 0, 0 };
    glm::vec3 vertical { 0, 2, 0 };
};
