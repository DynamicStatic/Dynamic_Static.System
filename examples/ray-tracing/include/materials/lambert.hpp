
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
#include "dynamic_static/system/gui.hpp"

namespace rtow {

class Lambert final
    : public Material
{
public:
    inline Lambert(const glm::vec3& albedo)
        : albedo { albedo }
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
        scatteredRay.direction = record.normal + random_unit_vector();
        attenuation = albedo;
        return true;
    }

    void gui() override final
    {
        ImGui::Text("Lambert");
        ImGui::Indent();
        ImGui::ColorPicker3("Albedo", &albedo[0]);
        ImGui::Unindent();
    }

    inline void bind() const override final
    {
        Material::bind();
        dst_gl(glUniform3f(get_uniform_location("albedo"), albedo.r, albedo.g, albedo.b));
    }

    glm::vec3 albedo { };
};

} // namespace rtow
