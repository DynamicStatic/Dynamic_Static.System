
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

#include "ray.hpp"

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/graphics/opengl/mesh.hpp"

#include <memory>
#include <vector>

namespace rtow {

class Material;

class Hittable
{
public:
    class Collection;

    struct Record final
    {
        inline void set_face_normal(const Ray& ray, const glm::vec3& outwardNormal)
        {
            frontFace = glm::dot(ray.direction, outwardNormal) < 0.0f;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }

        glm::vec3 point { };
        glm::vec3 normal { };
        const Material* pMaterial { };
        bool frontFace { };
        float t { };
    };

    virtual ~Hittable() = 0;
    virtual bool hit(const Ray& ray, float tMin, float tMax, Record& record) const = 0;
    virtual void draw() const = 0;

protected:
    dst::gl::Mesh mMesh;
};

inline Hittable::~Hittable()
{
}

class Hittable::Collection final
    : public std::vector<std::unique_ptr<Hittable>>
    , public Hittable
{
public:
    bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final
    {
        Record tempRecord { };
        bool hitAnything = false;
        auto closestHit = tMax;
        for (const auto& hittable : *this) {
            if (hittable->hit(ray, tMin, closestHit, tempRecord)) {
                hitAnything = true;
                closestHit = tempRecord.t;
                record = tempRecord;
            }
        }
        return hitAnything;
    }

    inline void draw() const override final
    {
        for (const auto& hittable : *this) {
            hittable->draw();
        }
    }
};

} // namespace rtow
