
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

#include "camera.hpp"
#include "ray.hpp"

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/core/transform.hpp"
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
        void set_face_normal(const Ray& ray, const glm::vec3& outwardNormal);
        glm::vec3 point { };
        glm::vec3 normal { };
        const Material* pMaterial { };
        bool frontFace { };
        float t { };
    };

    virtual ~Hittable() = 0;
    virtual bool hit(const Ray& ray, float tMin, float tMax, Record& record) const = 0;
    virtual void gui();
    virtual void draw(const Camera& camera);
    dst::Transform transform;

protected:
    dst::gl::Mesh mMesh;
    std::unique_ptr<Material> mpMaterial;
};

class Hittable::Collection final
    : public std::vector<std::unique_ptr<Hittable>>
    , public Hittable
{
public:
    bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final;
    void draw(const Camera& camera) override final;
};

} // namespace rtow
