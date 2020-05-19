
/*
===================================================================================
    Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
===================================================================================
*/

/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#if 0

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/system/opengl/shader.hpp"
#include "dynamic_static/system/opengl/vertex.hpp"

#include <array>

struct Vertex final
{
    glm::vec3 position { };
    glm::vec3 normal { };
};

namespace dst {
namespace sys {
namespace gl {

template <>
void enable_vertex_attributes<Vertex>()
{
    enable_vertex_attributes<Vertex, 2>({ {
        { GL_FLOAT, 3 },
        { GL_FLOAT, 3 },
    }});
}

} // namespace gl
} // namespace sys
} // namespace dst

class Gear final
{
public:
    class Renderer;

    inline Gear(
        float innerRadius,
        float outerRadius,
        float width,
        uint32_t teeth,
        float toothDepth
    )
    {
        std::vector<Vertex> vertices;
        auto createVertex = [&vertices](const glm::vec3& position)
        {
            auto index = (GLushort)vertices.size();
            vertices.push_back({ position, { } });
            return index;
        };
        std::vector<GLushort> indices;
        auto createFace = [&vertices, &indices](const std::array<GLushort, 3>& face)
        {
            std::copy_n(face.begin(), face.size(), std::back_inserter(indices));
        };
    }
};

class Gear::Renderer final
{
    std::array<dst::gl::Shader, 2> shaders {{
        {
            GL_VERTEX_SHADER,
            __LINE__,
            R"(
                #version 330
                uniform mat4 modelView;
                uniform mat4 projection;
                layout(location = 0) in vec3 vsPosition;
                layout(location = 1) in vec3 vsNormal;
                out vec3 fsNormal;
                out vec3 fsViewDirection;
                void main()
                {
                    vec4 position = modelView * vec4(vsPosition, 1);
                    gl_Position = projection * position;
                    fsNormal = normalize(modelView * vec4(vsNormal, 0)).xyz;
                    fsViewDirection = normalize(-position).xyz;
                }
            )"
        },
        {

        }
    }};
    std::array<Gear, 3> mGears {
        Gear { 1.0f, 4.f, 1.0f, 20, 0.7f },
        Gear { 0.5f, 2.f, 2.0f, 10, 0.7f },
        Gear { 1.3f, 2.f, 0.5f, 10, 0.7f },
    };
};

#endif
