
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
#include "dynamic_static/core/random.hpp"

namespace rtow {

static inline dst::RandomNumberGenerator& get_rng()
{
    thread_local dst::RandomNumberGenerator tlRng;
    return tlRng;
}

inline glm::vec3 random_vector_in_unit_sphere()
{
    while (true) {
        glm::vec3 vector {
            get_rng().range<float>(-1.0f, 1.0f),
            get_rng().range<float>(-1.0f, 1.0f),
            get_rng().range<float>(-1.0f, 1.0f),
        };
        if (1.0f <= glm::length2(vector)) {
            return vector;
        }
    }
}

inline glm::vec3 random_vector_in_hempisphere(const glm::vec3& normal)
{
    auto vector = random_vector_in_unit_sphere();
    return 0.0f < glm::dot(vector, normal) ? vector : -vector;
}

inline glm::vec3 random_unit_vector()
{
    auto a = get_rng().range<float>(0.0f, 2.0f * glm::pi<float>());
    auto z = get_rng().range<float>(-1.0f, 1.0f);
    auto r = glm::sqrt(1.0f - z * z);
    return { r * glm::cos(a), r * glm::sin(a), z };
}

inline float schlick(float cosine, float refractiveIndex)
{
    auto r0 = glm::pow((1.0f - refractiveIndex) / (1.0f + refractiveIndex), 2);
    return r0 + (1.0f - r0) * glm::pow((1.0f - cosine), 5.0f);
}

} // namespace rtow
