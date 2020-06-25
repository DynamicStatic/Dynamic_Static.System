
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

#include "hittable.hpp"
#include "ray.hpp"

#include "dynamic_static/core/math.hpp"

namespace rtow {

class Material
{
public:
    virtual bool scatter(
        const Ray& ray,
        const Hittable::Record& record,
        glm::vec3& attenuation,
        Ray& scatteredRay
    ) const = 0;
};

} // namespace rtow
