
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "hitable.hpp"
#include "ray.hpp"

#include "dynamic_static.core.hpp"

struct Sphere final
    : public Hitable
{
    Sphere(const glm::vec3& position, float radius)
        : position { position }
        , radius { radius }
    {
    }

    inline bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final
    {
        glm::vec3 oc = ray.origin - position;
        float a = glm::dot(ray.direction, ray.direction);
        float b = glm::dot(oc, ray.direction);
        float c = glm::dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0) {
            float temp = (-b - glm::sqrt(b * b - a * c)) / a;
            if (tMin < temp && temp < tMax) {
                record.t = temp;
                record.p = ray.point_at_parameter(record.t);
                record.normal = (record.p - position) / radius;
                return true;
            }
            temp = (-b + glm::sqrt(b * b - a * c)) / a;
            if (tMin < temp && temp < tMax) {
                record.t = temp;
                record.p = ray.point_at_parameter(record.t);
                record.normal = (record.p - position) / radius;
                return true;
            }
        }
        return false;
    }

    glm::vec3 position { };
    float radius { };
};
