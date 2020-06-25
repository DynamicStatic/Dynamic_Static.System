
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

#include <algorithm>

namespace rtow {

class Dialectric final
    : public Material
{
public:
    inline Dialectric(float refractiveIndex)
        : refractiveIndex { refractiveIndex }
    {
    }

    inline bool scatter(
        const Ray& ray,
        const Hittable::Record& record,
        glm::vec3& attenuation,
        Ray& scatteredRay
    ) const override final
    {
        attenuation = glm::vec3(1.0f);
        scatteredRay.origin = record.point;
        auto direction = glm::normalize(ray.direction);
        auto cosTheta = std::min(glm::dot(-direction, record.normal), 1.0f);
        auto sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);
        float etaiOverEtat = record.frontFace ? 1.0f / refractiveIndex : refractiveIndex;
        if (1.0f < etaiOverEtat * sinTheta) {
            scatteredRay.direction = glm::reflect(direction, record.normal);
        } else {
            if (get_rng().probability(schlick(cosTheta, etaiOverEtat))) {
                scatteredRay.direction = glm::reflect(direction, record.normal);
            } else {
                scatteredRay.direction = glm::refract(direction, record.normal, etaiOverEtat);
            }
        }
        return true;
    }

    float refractiveIndex { };
};

} // namespace rtow
