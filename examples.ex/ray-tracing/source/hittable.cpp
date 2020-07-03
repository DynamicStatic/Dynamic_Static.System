
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

#include "hittable.hpp"
#include "materials/material.hpp"

namespace rtow {

void Hittable::Record::set_face_normal(const Ray& ray, const glm::vec3& outwardNormal)
{
    frontFace = glm::dot(ray.direction, outwardNormal) < 0.0f;
    normal = frontFace ? outwardNormal : -outwardNormal;
}

Hittable::~Hittable()
{
}

void Hittable::gui()
{
    if (mpMaterial) {
        mpMaterial->gui();
    }
}

void Hittable::draw(const Camera& camera)
{
    if (mpMaterial) {
        auto modelMatrix = glm::translate(transform.translation);
        auto view = camera.view();
        auto projection = camera.projection();
        mpMaterial->bind();
        dst_gl(glUniformMatrix4fv(mpMaterial->get_uniform_location("model"), 1, GL_FALSE, &modelMatrix[0][0]));
        dst_gl(glUniformMatrix4fv(mpMaterial->get_uniform_location("view"), 1, GL_FALSE, &view[0][0]));
        dst_gl(glUniformMatrix4fv(mpMaterial->get_uniform_location("projection"), 1, GL_FALSE, &projection[0][0]));
        mMesh.draw_indexed();
        mMesh.fillMode = GL_LINE;
        mpMaterial->unbind();
    }
}

bool Hittable::Collection::hit(const Ray& ray, float tMin, float tMax, Record& record) const
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

void Hittable::Collection::draw(const Camera& camera)
{
    for (const auto& hittable : *this) {
        hittable->draw(camera);
    }
}

} // namespace rtow
