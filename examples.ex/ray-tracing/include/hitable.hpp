
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

#include <memory>
#include <vector>

class Hitable
{
public:
    class Collection;

    struct Record final
    {
        float t { };
        glm::vec3 p { };
        glm::vec3 normal { };
    };

    virtual ~Hitable() = 0
    {
    }

    virtual bool hit(const Ray& ray, float tMin, float tMax, Record& record) const = 0;
};

class Hitable::Collection final
    : public Hitable
{
public:
    inline bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final
    {
        Record tempRecord { };
        bool hitAnything = false;
        float closestSoFar = tMax;
        for (const auto& hitable : hitables) {
            if (hitable->hit(ray, tMin, closestSoFar, tempRecord)) {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }
        return hitAnything;
    }

    std::vector<std::unique_ptr<Hitable>> hitables;
};
