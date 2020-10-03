
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
#include "camera.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "sphere-indices.hpp"
#include "sphere-vertices.hpp"

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <map>
#include <set>

namespace dst {
namespace sys {
namespace gl {

template <>
inline void enable_vertex_attributes<glm::vec3>()
{
    enable_vertex_attributes<glm::vec3, 3>({{
        { GL_FLOAT, 3 },
    }});
}

} // namespace gl
} // namespace sys
} // namespace dst

namespace rtow {

inline void generate_icosahedron_vertices(
    std::vector<glm::vec3>& vertices,
    std::vector<uint32_t>& indices,
    float radius = 0.5f
)
{
    vertices.clear();
    vertices.resize(12);
    vertices[0].y = radius;
    vertices[11].y = -radius;
    const glm::vec2 Angles { glm::two_pi<float>() / 10.0f, 0.5f };
    for (size_t i = 1; i <= 10; ++i) {
        auto theta = Angles.x * (float)i;
        vertices[i].x = glm::cos(theta);
        vertices[i].y = glm::atan(i % 2 ? Angles.y : -Angles.y);
        vertices[i].z = glm::sin(theta);
        vertices[i] = glm::normalize(vertices[i]) * radius;
    }
    indices = {
        0, 1, 3, 0, 3, 5, 0, 5, 7, 0, 7, 9, 0, 9, 1,
        1, 3, 2,
        2, 3, 4,
        3, 5, 4,
        4, 5, 6,
        5, 7, 6,
        6, 7, 8,
        7, 9, 8,
        8, 9, 10,
        9, 1, 10,
        11, 10, 8, 11, 8, 6, 11, 6, 4, 11, 4, 2, 11, 2, 10
    };
}

inline void subdivide_icosahedron_vertices(
    std::vector<glm::vec3>& vertices,
    std::vector<uint32_t>& indices
)
{
    auto addVertex = [&](const glm::vec3& vertex)
    {
        auto index = vertices.size();
        vertices.push_back(vertex);
        return index;
    };
    auto addTriangle = [&](const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
    {

    };
    auto radius = glm::length(vertices[0]);
    std::map<glm::vec3, uint32_t> uniqueVertices;
    if (vertices.size() == 12 && indices.size() == 57) {
        size_t indexCount = indices.size();
        for (size_t i = 0; i < indexCount; i += 3) {
            auto i0 = indices[i];
            auto i1 = indices[i + 1];
            auto i2 = indices[i + 2];
            auto& vertex0 = vertices[i0];
            auto& vertex1 = vertices[i1];
            auto& vertex2 = vertices[i2];
            auto newVertex0 = glm::normalize((vertex0 + vertex1) * 0.5f) * radius;
            auto newVertex1 = glm::normalize((vertex1 + vertex2) * 0.5f) * radius;
            auto newVertex2 = glm::normalize((vertex2 + vertex0) * 0.5f) * radius;
            auto i0p = addVertex(newVertex0);
            auto i1p = addVertex(newVertex1);
            auto i2p = addVertex(newVertex2);

#if 0
            auto newVertex0 = glm::normalize((vertex0 + vertex1) * 0.5f) * radius;
            auto newVertex1 = glm::normalize((vertex1 + vertex2) * 0.5f) * radius;
            auto newVertex2 = glm::normalize((vertex2 + vertex0) * 0.5f) * radius;
            indices.push_back(vertices.size());
            vertices.push_back(newVertex0);
            indices.push_back(vertices.size());
            vertices.push_back(newVertex1);
            indices.push_back(vertices.size());
            vertices.push_back(newVertex2);
#endif
        }
    }
}

class Sphere final
    : public Hittable
{
public:
    Sphere() = default;
    inline Sphere(const glm::vec3& position, float radius, std::unique_ptr<Material>&& material)
        : radius { radius }
    {
#if 1
        std::vector<glm::vec3> v;
        std::vector<uint32_t> i;
        generate_icosahedron_vertices(v, i, radius);
        mMesh.write<glm::vec3, uint32_t>(v, i);
#endif

#if 1
        transform.translation = position;
        mpMaterial = std::move(material);
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;
        const uint32_t VertexCount = 128;
        const float Theta = glm::two_pi<float>() / VertexCount;
        for (uint32_t i = 0; i < VertexCount; ++i) {
            auto theta = Theta * (float)i;
            glm::vec3 vertex { glm::cos(theta), glm::sin(theta), 0.0f };
            vertex = glm::normalize(vertex) * radius;
            vertices.push_back(vertex);
        }
        for (uint32_t i = 2; i < VertexCount; ++i) {
            indices.push_back(0);
            indices.push_back(i - 1);
            indices.push_back(i);
        }
        // mMesh.write<glm::vec3, uint32_t>(vertices, indices);
        if (vertices != v || indices != i) {
            int b = 0;
        }
#endif
    }

    inline bool hit(const Ray& ray, float tMin, float tMax, Record& record) const override final
    {
        glm::vec3 op = ray.origin - transform.translation;
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
                record.set_face_normal(ray, (record.point - transform.translation) / radius);
                record.pMaterial = mpMaterial.get();
                return true;
            }
            temp = (-halfB + root) / a;
            if (tMin < temp && temp < tMax) {
                record.t = temp;
                record.point = ray.at(record.t);
                record.set_face_normal(ray, (record.point - transform.translation) / radius);
                record.pMaterial = mpMaterial.get();
                return true;
            }
        }
        return false;
    }

    float radius { };
};

} // namespace rtow
