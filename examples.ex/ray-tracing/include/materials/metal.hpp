
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

#include "materials/material.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "utilities.hpp"

#include "dynamic_static/core/math.hpp"

namespace rtow {

class Metal final
    : public Material
{
public:
    inline Metal(const glm::vec3& albedo, float fuzz)
        : albedo { albedo }
        , roughness { fuzz < 1.0f ? fuzz : 1.0f }
    {
    }

    inline bool scatter(
        const Ray& ray,
        const Hittable::Record& record,
        glm::vec3& attenuation,
        Ray& scatteredRay
    ) const override final
    {
        scatteredRay.origin = record.point;
        auto reflectedDirection = glm::reflect(glm::normalize(ray.direction), record.normal);
        scatteredRay.direction = reflectedDirection + random_vector_in_unit_sphere() * roughness;
        attenuation = albedo;
        return 0.0f < glm::dot(scatteredRay.direction, record.normal);
    }

    glm::vec3 albedo { };
    float roughness { 1.0f };
};

} // namespace rtow
