
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

// FROM : Based on Peter Shirley's "Ray Tracing in One Weekend" series
//  https://raytracing.github.io/

#pragma once

#include "dynamic_static/core/math.hpp"

namespace rtow {

struct Ray final
{
    glm::vec3 at(float t) const
    {
        return origin + direction * t;
    }

    glm::vec3 origin { };
    glm::vec3 direction { };
};

} // namespace rtow
