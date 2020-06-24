
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "hittable.hpp"
#include "ray.hpp"

namespace rtow {

class Sphere final
    : public Hittable
{
public:
    Sphere() = default;
    inline Sphere(const glm::vec3& position, float radius)
        : position { position }
        , radius { radius }
    {
    }

private:
    inline bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final
    {
        glm::vec3 op = ray.origin - position;
        auto a = glm::length2(ray.direction);
        auto halfB = glm::dot(op, ray.direction);
        auto c = glm::length2(op) - radius * radius;
        auto discriminant = halfB * halfB - a * c;
        if (0 < discriminant) {
            auto root = glm::sqrt(discriminant);
            auto temp = (-halfB - root) / a;
            if (tMin < temp && temp < tMax) {
                record.t = temp;
                record.point = ray.at(record.t);
                record.set_face_normal(ray, (record.point - position) / radius);
                return true;
            }
            temp = (-halfB + root) / a;
            if (tMin < temp && temp < tMax) {
                record.t = temp;
                record.point = ray.at(record.t);
                record.set_face_normal(ray, (record.point - position) / radius);
                return true;
            }
        }
        return false;
    }

public:
    glm::vec3 position { };
    float radius { };
};

} // namespace rtow
