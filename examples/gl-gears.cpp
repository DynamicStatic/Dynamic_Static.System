
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

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <array>
#include <iostream>
#include <utility>
#include <vector>

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
    enable_vertex_attributes<Vertex, 2>({{
        { GL_FLOAT, 3 },
        { GL_FLOAT, 3 }
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
        auto createVertex =
        [&vertices](const glm::vec3& position)
        {
            auto index = (GLushort)vertices.size();
            vertices.push_back({ position, { } });
            return index;
        };

        std::vector<GLushort> indices;
        auto createFace =
        [&vertices, &indices](const std::array<GLushort, 3>& face)
        {
            std::copy_n(face.begin(), face.size(), std::back_inserter(indices));
        };

        const glm::vec3 w { 0, 0, width * 0.5f };
        const float pi = (float)M_PI;
        const float toothAngle = 2.0f * pi / teeth;
        const float toothDivisionsAngle = toothAngle / 4;
        const float toothInnerRadius = outerRadius - toothDepth * 0.5f;
        const float toothOuterRadius = outerRadius + toothDepth * 0.5f;
        for (uint32_t tooth_i = 0; tooth_i < teeth; ++tooth_i) {
            float angle = toothAngle * tooth_i;
            std::array<glm::vec3, 5> anchors { };
            for (size_t anchor_i = 0; anchor_i < anchors.size(); ++anchor_i) {
                anchors[anchor_i].x = cos(angle + toothDivisionsAngle * anchor_i);
                anchors[anchor_i].y = sin(angle + toothDivisionsAngle * anchor_i);
                anchors[anchor_i] = glm::normalize(anchors[anchor_i]);
            }
            {
                auto i0 = createVertex(anchors[1] * toothOuterRadius - w);
                auto i1 = createVertex(anchors[2] * toothOuterRadius - w);
                auto i2 = createVertex(anchors[3] * toothInnerRadius - w);
                auto i3 = createVertex(anchors[0] * toothInnerRadius - w);
                auto i4 = createVertex(anchors[4] * innerRadius      - w);
                auto i5 = createVertex(anchors[0] * innerRadius      - w);
                auto i6 = createVertex(anchors[4] * toothInnerRadius - w);
                createFace({ i0, i1, i2 });
                createFace({ i0, i2, i3 });
                createFace({ i3, i2, i4 });
                createFace({ i3, i4, i5 });
                createFace({ i2, i6, i4 });
            }
            {
                auto i0 = createVertex(anchors[1] * toothOuterRadius + w);
                auto i1 = createVertex(anchors[2] * toothOuterRadius + w);
                auto i2 = createVertex(anchors[3] * toothInnerRadius + w);
                auto i3 = createVertex(anchors[0] * toothInnerRadius + w);
                auto i4 = createVertex(anchors[4] * innerRadius      + w);
                auto i5 = createVertex(anchors[0] * innerRadius      + w);
                auto i6 = createVertex(anchors[4] * toothInnerRadius + w);
                createFace({ i0, i2, i1 });
                createFace({ i0, i3, i2 });
                createFace({ i3, i4, i2 });
                createFace({ i3, i5, i4 });
                createFace({ i2, i4, i6 });
            }
            {
                auto i0 = createVertex(anchors[0] * toothInnerRadius + w);
                auto i1 = createVertex(anchors[1] * toothOuterRadius + w);
                auto i2 = createVertex(anchors[2] * toothOuterRadius + w);
                auto i3 = createVertex(anchors[3] * toothInnerRadius + w);
                auto i4 = createVertex(anchors[4] * toothInnerRadius + w);
                auto i5 = createVertex(anchors[0] * toothInnerRadius - w);
                auto i6 = createVertex(anchors[1] * toothOuterRadius - w);
                auto i7 = createVertex(anchors[2] * toothOuterRadius - w);
                auto i8 = createVertex(anchors[3] * toothInnerRadius - w);
                auto i9 = createVertex(anchors[4] * toothInnerRadius - w);
                createFace({ i0, i1, i6 });
                createFace({ i0, i6, i5 });
                createFace({ i1, i2, i7 });
                createFace({ i1, i7, i6 });
                createFace({ i2, i3, i8 });
                createFace({ i2, i8, i7 });
                createFace({ i3, i4, i9 });
                createFace({ i3, i9, i8 });
            }
        }

        GLushort i00 { }, i01 { }, si0 { }, si1 { };
        for (uint32_t tooth_i = 0; tooth_i < teeth; ++tooth_i) {
            float angle = toothAngle * tooth_i;
            std::array<glm::vec3, 2> anchors { };
            for (size_t anchor_i = 0; anchor_i < anchors.size(); ++anchor_i) {
                anchors[anchor_i].x = cos(angle + toothAngle * anchor_i);
                anchors[anchor_i].y = sin(angle + toothAngle * anchor_i);
                anchors[anchor_i] = glm::normalize(anchors[anchor_i]);
            }
            if (!i00 && !i01) {
                i00 = si0 = createVertex(anchors[0] * innerRadius + w);
                i01 = si1 = createVertex(anchors[0] * innerRadius - w);
            }
            auto i0 = tooth_i < teeth - 1 ? createVertex(anchors[1] * innerRadius + w) : si0;
            auto i1 = tooth_i < teeth - 1 ? createVertex(anchors[1] * innerRadius - w) : si1;
            createFace({ i00, i01, i0 });
            createFace({ i01, i1,  i0 });
            i00 = i0;
            i01 = i1;
        }

        std::vector<uint32_t> hits(vertices.size());
        for (size_t i = 0; i < indices.size(); i += 3) {
            auto& v0 = vertices[indices[i]];
            auto& v1 = vertices[indices[i + 1]];
            auto& v2 = vertices[indices[i + 2]];
            auto edge0 = v0.position - v1.position;
            auto edge1 = v0.position - v2.position;
            glm::vec3 normal = -glm::normalize(glm::cross(edge0, edge1));
            v0.normal = glm::normalize(v0.normal + normal);
            v1.normal = glm::normalize(v1.normal + normal);
            v2.normal = glm::normalize(v2.normal + normal);
            ++hits[indices[i]];
            ++hits[indices[i + 1]];
            ++hits[indices[i + 2]];
        }

        for (size_t i = 0; i < vertices.size(); ++i) {
            vertices[i].normal /= (float)hits[i];
            vertices[i].normal = glm::normalize(vertices[i].normal);
        }

        mesh.write<Vertex, GLushort>(vertices, indices);
    }

    glm::vec3 position { };
    glm::vec4 color { };
    float rotation { };
    float speed { };
    dst::sys::gl::Mesh mesh;
};

class Gear::Renderer final
{
public:
    inline Renderer()
    {
        gears[0].position = { -3.f, -2.f, 0.0f };
        gears[0].color = { 0.8f, 0.1f, 0.0f, 1.0f };
        gears[1].rotation = 0;
        gears[0].speed = 70;

        gears[1].position = { 3.1f, -2.0f, 0.0f };
        gears[1].color = { 0.0f, 0.8f, 0.2f, 1.0 };
        gears[1].rotation = -9;
        gears[1].speed = -140;

        gears[2].position = { -3.1f, 4.2f, 0.0f };
        gears[2].color = { 0.2f, 0.2f, 1.0f, 1.0f };
        gears[2].rotation = -25;
        gears[2].speed = -140;
    }

    inline void update(float deltaTime, const dst::sys::Input& input)
    {
        using namespace dst::sys;
        if (input.keyboard.pressed(Keyboard::Key::A)) {
            animation = !animation;
        }
        if (input.keyboard.pressed(Keyboard::Key::W)) {
            wireFrame = !wireFrame;
        }
        if (input.mouse.down(Mouse::Button::Left)) {
            auto look = input.mouse.position_delta() * lookSensitivity * deltaTime;
            auto rotationX = glm::angleAxis(look.y, glm::vec3 { 1, 0, 0 });
            auto rotationY = glm::angleAxis(look.x, glm::vec3 { 0, 1, 0 });
            worldRotation = glm::normalize(rotationX * rotationY * worldRotation);
        }
        cameraPosition.z -= input.mouse.scroll_delta() * scrollSensitivity * deltaTime;
        if (input.mouse.down(Mouse::Button::Middle) ||
            input.mouse.down(Mouse::Button::Right)) {
            cameraPosition.x -= input.mouse.position_delta().x * cameraSpeed * deltaTime;
            cameraPosition.y += input.mouse.position_delta().y * cameraSpeed * deltaTime;
        }
    }

    inline void draw(float deltaTime, const glm::ivec2& viewport)
    {
        auto viewMatrix = glm::lookAt(
            cameraPosition,
            cameraPosition + glm::vec3 { 0, 0, -1 },
            { 0, 1, 0 }
        );
        auto projectionMatrix = glm::perspective(
            glm::radians(fieldOfView),
            dst::aspect_ratio<glm::ivec2>(viewport),
            0.001f,
            100.0f
        );
        dst_gl(glEnable(GL_CULL_FACE));
        dst_gl(glCullFace(GL_BACK));
        dst_gl(glEnable(GL_DEPTH_TEST));
        dst_gl(glViewport(0, 0, viewport.x, viewport.y));
        dst_gl(glClearColor(0, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        program.bind();
        dst_gl(glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]));
        dst_gl(glUniform3fv(lightDirectionLocation, 1, &glm::normalize(lightDirection)[0]));
        for (auto& gear : gears) {
            gear.rotation += animation ? gear.speed * deltaTime : 0;
            auto modelMatrix =
                glm::toMat4(worldRotation) *
                glm::translate(gear.position) *
                glm::rotate(glm::radians(gear.rotation), glm::vec3 { 0, 0, 1 });
            auto modelViewMatrix = viewMatrix * modelMatrix;
            dst_gl(glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelViewMatrix[0][0]));
            dst_gl(glUniform4fv(colorLocation, 1, &gear.color[0]));
            gear.mesh.fillMode = wireFrame ? GL_LINE : GL_FILL;
            gear.mesh.draw_indexed();
        }
        program.unbind();
    }

    bool animation { true };
    bool wireFrame { false };
    float fieldOfView { 40 };
    float cameraSpeed { 7.4f };
    float scrollSensitivity { 86 };
    glm::vec2 lookSensitivity { 1.6f };
    glm::vec3 lightDirection { -5, -5, -10 };
    glm::vec3 cameraPosition { 0, 0, 20 };
    glm::quat worldRotation {
        glm::normalize(
            glm::angleAxis(glm::radians(20.0f), glm::vec3 { 1, 0, 0 }) *
            glm::angleAxis(glm::radians(30.0f), glm::vec3 { 0, 1, 0 })
        )
    };
    std::array<dst::sys::gl::Shader, 2> shaders {{
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
            GL_FRAGMENT_SHADER,
            __LINE__,
            R"(
                #version 330
                uniform vec4 color;
                uniform vec3 lightDirection;
                in vec3 fsNormal;
                in vec3 fsViewDirection;
                out vec4 fragColor;
                void main()
                {
                    vec3 reflection = normalize(reflect(lightDirection, fsNormal));
                    vec4 ambient = vec4(0.2, 0.2, 0.2, 1);
                    vec4 diffuse = vec4(0.5) * max(dot(fsNormal, -lightDirection), 0);
                    float specularPower = 0.25;
                    vec4 specular = vec4(0.5, 0.5, 0.5, 1) * pow(max(dot(reflection, fsViewDirection), 0), 0.8) * specularPower;
                    fragColor = vec4((ambient + diffuse) * color + specular);
                }
            )"
        }
    }};
    dst::sys::gl::Program program { shaders };
    GLint modelViewLocation { program.uniform_location("modelView") };
    GLint projectionLocation { program.uniform_location("projection") };
    GLint colorLocation { program.uniform_location("color") };
    GLint lightDirectionLocation { program.uniform_location("lightDirection") };
    std::array<Gear, 3> gears {
        Gear { 1.0f, 4.f, 1.0f, 20, 0.7f },
        Gear { 0.5f, 2.f, 2.0f, 10, 0.7f },
        Gear { 1.3f, 2.f, 0.5f, 10, 0.7f },
    };
};

int main()
{
    std::cout << std::endl;
    std::cout << "[Esc]          - Quit" << std::endl;
    std::cout << "[A]            - Toggle animation" << std::endl;
    std::cout << "[W]            - Toggle wire frame" << std::endl;
    std::cout << "[Left Mouse]   - Rotate model" << std::endl;
    std::cout << "[Scroll Wheel] - Move model forward and backward" << std::endl;
    std::cout << "[Middle Mouse] - Move model horizontally and vertically" << std::endl;
    std::cout << "[Right Mouse]  - Move model horizontally and vertically" << std::endl;
    std::cout << std::endl;

    using namespace dst;
    using namespace dst::sys;
    Window::GlInfo glInfo { };
    Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static GL Gears";
    windowInfo.pGlInfo = &glInfo;
    Window window(windowInfo);
    Delegate<const Window&> window_close_requested_handler;
    window.on_close_requested += window_close_requested_handler;
    bool closeRequested = false;
    window_close_requested_handler =
        [&](const Window&)
        {
            closeRequested = true;
        };

    Gear::Renderer renderer;
    dst::Clock clock;
    while (!closeRequested && !window.get_input().keyboard.down(Keyboard::Key::Escape)) {
        clock.update();
        Window::poll_events();
        auto deltaTime = clock.elapsed<dst::Seconds<float>>();
        renderer.update(deltaTime, window.get_input());
        renderer.draw(deltaTime, window.get_info().extent);
        window.swap();
    }
    return 0;
}
