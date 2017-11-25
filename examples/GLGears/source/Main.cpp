
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
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Math.hpp"
#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/System/GLInclude.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Window.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct Vertex final
{
    glm::vec3 position;
    glm::vec3 normal;

    static void enable_attributes()
    {
        GLuint index = 0;
        size_t offset = 0;
        Vertex* vertex = nullptr;

        dst_gl(glEnableVertexAttribArray(index));
        dst_gl(glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offset));
        offset += sizeof(vertex->position);
        ++index;

        dst_gl(glEnableVertexAttribArray(index));
        dst_gl(glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offset));
        offset += sizeof(vertex->normal);
        ++index;
    }
};

struct Mesh final
{
    GLuint vertexArray { 0 };
    GLuint vertexBuffer { 0 };
    GLuint indexBuffer { 0 };
    GLsizei indexCount { 0 };
    GLenum indexType { GL_UNSIGNED_SHORT };
    GLenum primitiveType { GL_TRIANGLES };
    GLenum winding { GL_CW };

    Mesh()
    {
        dst_gl(glGenVertexArrays(1, &vertexArray));
        dst_gl(glGenBuffers(1, &vertexBuffer));
        dst_gl(glGenBuffers(1, &indexBuffer));
    }

    ~Mesh()
    {
        dst_gl(glDeleteVertexArrays(1, &vertexArray));
        dst_gl(glDeleteBuffers(1, &vertexBuffer));
        dst_gl(glDeleteBuffers(1, &indexBuffer));
    }

    template <typename VertexType, typename IndexType>
    void write(
        const std::vector<VertexType>& vertices,
        const std::vector<IndexType>& indices,
        GLenum primitiveType = GL_TRIANGLES,
        GLenum winding = GL_CW
    )
    {
        dst_gl(glBindVertexArray(vertexArray));
        dst_gl(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        dst_gl(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW));
        dst_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
        dst_gl(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW));
        VertexType::enable_attributes();
        dst_gl(glBindBuffer(GL_ARRAY_BUFFER, 0));
        dst_gl(glBindVertexArray(0));

        indexCount = static_cast<GLsizei>(indices.size());
        switch (sizeof(indices[0])) {
            case sizeof(GLubyte) : indexType = GL_UNSIGNED_BYTE; break;
            case sizeof(GLushort) : indexType = GL_UNSIGNED_SHORT; break;
            case sizeof(GLuint) : indexType = GL_UNSIGNED_INT; break;
        }

        this->primitiveType = primitiveType;
        this->winding = winding;
    }
};

struct Shader final
{
public:
    GLuint handle { 0 };

public:
    Shader(GLenum stage, const std::string& source)
    {
        handle = glCreateShader(stage);
        auto sourceCStr = source.c_str();
        dst_gl(glShaderSource(handle, 1, &sourceCStr, nullptr));
        dst_gl(glCompileShader(handle));
        GLint compileStatus;
        dst_gl(glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus));
        if (compileStatus != GL_TRUE) {
            char log[1024];
            GLsizei logSize;
            dst_gl(glGetShaderInfoLog(handle, sizeof(log), &logSize, log));
            std::string stageStr;
            switch (stage) {
                case GL_VERTEX_SHADER: stageStr = "vertex"; break;
                case GL_FRAGMENT_SHADER: stageStr = "fragment"; break;
                default: stageStr = "unknown";
            }

            std::cerr << "Failed to compile " << stageStr << " shader" << std::endl;
            std::cerr << log << std::endl;
            std::cerr << std::endl;
            dst_gl(glDeleteShader(handle));
            handle = 0;
        }
    }

    ~Shader()
    {
        dst_gl(glDeleteShader(handle));
    }
};

struct Program final
{
public:
    GLuint handle { 0 };

public:
    Program(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    {
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource);
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        dst_gl(handle = glCreateProgram());
        dst_gl(glAttachShader(handle, vertexShader.handle));
        dst_gl(glAttachShader(handle, fragmentShader.handle));
        dst_gl(glLinkProgram(handle));
        GLint linkStatus;
        dst_gl(glGetProgramiv(handle, GL_LINK_STATUS, &linkStatus));
        if (linkStatus != GL_TRUE) {
            char log[1024];
            GLsizei logSize;
            dst_gl(glGetProgramInfoLog(handle, sizeof(log), &logSize, log));
            std::cerr << "Failed to link program" << std::endl;
            std::cerr << log << std::endl;
            std::cerr << std::endl;
            dst_gl(glDeleteProgram(handle));
            handle = 0;
        }
    }

    ~Program()
    {
        glDeleteProgram(handle);
    }
};

struct Gear final
{
public:
    dst::Vector3 position;
    float rotationSpeed { 1 };
    float rotation { 0 };
    dst::Color diffuseColor;
    dst::Color specularColor;
    float specularPower;
    Mesh mesh;

public:
    Gear(
        float innerRadius,
        float outerRadius,
        float width,
        uint32_t teeth,
        float toothDepth
    )
    {
        std::vector<Vertex> vertices;
        auto createVertex =
        [&vertices](const dst::Vector3& position)
        {
            vertices.push_back({ position, { }});
            return static_cast<GLushort>(vertices.size() - 1);
        };

        std::vector<GLushort> indices;
        auto createFace =
        [&vertices, &indices](const std::array<GLushort, 3>& face)
        {
            std::copy_n(face.begin(), face.size(), std::back_inserter(indices));
        };

        const dst::Vector3 w(0, 0, width * 0.5f);
        const float pi = static_cast<float>(M_PI);
        const float tootAngle = 2.0f * pi / teeth;
        const float toothDivisionsAngle = tootAngle / 4;
        const float toothInnerRadius = outerRadius - toothDepth * 0.5f;
        const float toothOuterRadius = outerRadius + toothDepth * 0.5f;
        for (uint32_t tooth_i = 0; tooth_i < teeth; ++tooth_i) {
            float angle = tootAngle * tooth_i;
            std::array<dst::Vector3, 5> anchors;
            for (size_t anchor_i = 0; anchor_i < anchors.size(); ++anchor_i) {
                anchors[anchor_i].x = cos(angle + toothDivisionsAngle * anchor_i);
                anchors[anchor_i].y = sin(angle + toothDivisionsAngle * anchor_i);
            }

            {
                /*

                    NOTE : Front face vertex indices with anchor index, clockwise winding...

                                           i0      i1
                                           a1      a2
                          toothOuterRadius  +------+
                                           /        \
                                          /          \
                                      i3 /            \ i2
                                      a0/              \a3
                     toothInnerRadius  +----------------+..      i6
                                       \                /  `..   a4
                                        \              /       `..  toothInnerRadius
                                         \            /         /
                                          \          /      /
                                           \        /   /
                               innerRadius  +------+
                                           i5      i4
                                           a0      a4

                */

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
                // NOTE : Back face...same as the front face with opposite winding order and positive w...
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
                /*

                    NOTE : Outer surface vertex indices with anchor index, clockwise winding...

                          toothOuterRadius  +------+  toothOuterRadius
                                          /          \
                                         /            \  /toothInnerRadius
                     toothInnerRadius  +                +--------+ toothInnerRadius

                                      a0   a1     a2   a3       a4
                                      i0   i1     i2   i3       i4
                                       +----+------+----+--------+ +w
                                       |    |      |    |        |
                                       |    |      |    |        |
                                       |    |      |    |        |
                                       +----+------+----+--------+ -w
                                      a0   a1     a2   a3       a4
                                      i5   i6     i7   i8       i9

                */

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

            {
                // NOTE : Inner cylinder face...matches the vertices at i4 and i5 for the front and back faces...
                auto i0 = createVertex(anchors[0] * innerRadius - w);
                auto i1 = createVertex(anchors[4] * innerRadius - w);
                auto i2 = createVertex(anchors[4] * innerRadius + w);
                auto i3 = createVertex(anchors[0] * innerRadius + w);
                createFace({ i0, i1, i2 });
                createFace({ i0, i2, i3 });
            }
        }

        std::vector<uint32_t> hits(vertices.size());
        for (size_t i = 0; i < indices.size(); i += 3) {
            auto& v0 = vertices[indices[i]];
            auto& v1 = vertices[indices[i + 1]];
            auto& v2 = vertices[indices[i + 2]];
            auto edge0 = v0.position - v1.position;
            auto edge1 = v0.position - v2.position;
            glm::vec3 normal = -glm::normalize(glm::cross(edge0, edge1));
            v0.normal += normal;
            v1.normal += normal;
            v2.normal += normal;
            ++hits[indices[i]];
            ++hits[indices[i + 1]];
            ++hits[indices[i + 2]];
        }

        for (size_t i = 0; i < vertices.size(); ++i) {
            vertices[i].normal /= hits[i];
            vertices[i].normal = glm::normalize(vertices[i].normal);
        }

        mesh.write(vertices, indices);
    }
};

int main()
{
    dst::sys::Window::Configuration windowConfiguration;
    windowConfiguration.name = "GLGears";
    windowConfiguration.api = dst::sys::API::OpenGL;
    windowConfiguration.apiVersion.major = 3;
    windowConfiguration.apiVersion.minor = 3;
    windowConfiguration.resolution.width = 1280;
    windowConfiguration.resolution.height = 720;
    dst::sys::Window window(windowConfiguration);

    std::array<Gear, 3> gears {
        Gear(1.0f, 4.0f, 1.0f, 20, 0.7f),
        Gear(0.5f, 2.0f, 2.0f, 10, 0.7f),
        Gear(1.3f, 2.0f, 0.5f, 10, 0.7f)
    };

    gears[0].position = dst::Vector3(-3.0f,  0.0f, 0.0f);
    gears[0].diffuseColor = dst::Color(0.8f, 0.1f, 0.0f, 1.0f);
    gears[2].specularColor = dst::Color::White;
    gears[2].specularPower = 0;
    gears[0].rotationSpeed = 1;

    gears[1].position = dst::Vector3( 3.1f,  0.0f, 0.0f);
    gears[1].diffuseColor = dst::Color(0.0f, 0.8f, 0.2f, 1.0);
    gears[2].specularColor = dst::Color::White;
    gears[2].specularPower = 0;
    gears[1].rotationSpeed = -2;

    gears[2].position = dst::Vector3(-3.1f, -6.2f, 0.0f);
    gears[2].diffuseColor = dst::Color(0.2f, 0.2f, 1.0f, 1.0f);
    gears[2].specularColor = dst::Color::White;
    gears[2].specularPower = 0;
    gears[2].rotationSpeed = -2;

    Program program(
        R"(
            #version 330
            // uniform vec4 color;


            uniform mat4 modelView;
            uniform mat4 projection;


            // uniform mat4 model;
            // uniform mat4 view;
            // uniform mat4 projection;
            // uniform vec3 lightDirection;


            layout(location = 0) in vec3 vsPosition;
            layout(location = 1) in vec3 vsNormal;


            // out vec4 fsColor;

            out vec4 fsNormal;
            out vec4 fsViewSpacePosition;

            void main()
            {
                fsNormal = normalize(modelView * vec4(vsNormal, 0));
                fsViewSpacePosition = modelView * vec4(vsPosition, 1);
                gl_Position = projection * fsViewSpacePosition;



                // mat4 modelView = view * model;
                // vec4 position = modelView * vec4(vsPosition, 1);
                // vec3 n = normalize((model * vec4(vsNormal, 0)).xyz);
                // vec3 l = lightDirection.xyz;
                // // vec3 l = normalize((view * vec4(-lightDirection, 1)).xyz);
                // fsColor = color * dot(n, l);
                // // fsColor += vec4(1, 1, 1, 1);
                // // fsColor *= 0.001;
                // // fsColor += vec4(n, 1);
                // gl_Position = projection * position;
            }
        )",
        R"(
            #version 330
            // uniform vec4 lightColor;
            // uniform vec4 ambientColor;
            // uniform float ambientIntensity;
            // uniform vec4 diffuseColor;
            // uniform vec4 specularColor;
            // uniform vec4 specularPower;

            uniform vec4 color;
            uniform vec3 lightDirection;
            

            // in vec4 fsColor;

            in vec4 fsNormal;
            in vec4 fsViewSpacePosition;

            out vec4 fragColor;


            void main()
            {
                fragColor = color + vec4(lightDirection, 1) * fsNormal * fsViewSpacePosition;
                fragColor *= 0.0001;
                fragColor += color;

                // float4 normal = normalize(fsNormal);
                // float4 diffuse = diffuseColor * dot(n, l);
                // 
                // fragColor = fsColor;
            }
        )"
    );

    GLint modelViewLocation;
    GLint projectionLocation;
    GLint colorLocation;
    GLint lightDirectionLocation;
    dst_gl(modelViewLocation = glGetUniformLocation(program.handle, "modelView"));
    dst_gl(projectionLocation = glGetUniformLocation(program.handle, "projection"));
    dst_gl(colorLocation = glGetUniformLocation(program.handle, "color"));
    dst_gl(lightDirectionLocation = glGetUniformLocation(program.handle, "lightDirection"));

    dst_gl(glEnable(GL_CULL_FACE));
    dst_gl(glEnable(GL_DEPTH_TEST));

    bool lines = true;
    float fieldOfView = 60;
    float cameraSpeed = 7.4f;
    float scrollSensitivity = 86;
    dst::Vector2 lookSensitivity(1.6f);
    // glm::vec3 cameraPosition(-1, -1.5f, -16);
    dst::Quaternion worldRotation;
    dst::Vector3 cameraPosition(0, 0, -16);
    dst::Vector3 lightDirection(0, 1, -1);

    dst::Clock clock;
    bool running = true;
    while (running) {
        dst::sys::Window::update();
        const auto& input = window.get_input();

        clock.update();
        auto dt = clock.elapsed<dst::Second<float>>();

        if (input.get_keyboard().down(dst::sys::Keyboard::Key::Escape)) {
            running = false;
        }

        if (input.get_keyboard().pressed(dst::sys::Keyboard::Key::Tab)) {
            lines = !lines;
        }

        if (input.get_keyboard().down(dst::sys::Keyboard::Key::Q)) {
            cameraPosition.y += cameraSpeed * dt;
        }

        if (input.get_keyboard().down(dst::sys::Keyboard::Key::E)) {
            cameraPosition.y -= cameraSpeed * dt;
        }

        if (input.get_mouse().down(dst::sys::Mouse::Button::Left)) {
            auto look = input.get_mouse().delta() * lookSensitivity * dt;
            auto rotationX = dst::Quaternion(-look.y, dst::Vector3::UnitX);
            auto rotationY = dst::Quaternion( look.x, dst::Vector3::UnitY);
            worldRotation = rotationY * worldRotation * rotationX;
            worldRotation.normalize();
        }

        cameraPosition.z += static_cast<float>(input.get_mouse().scroll() * scrollSensitivity * dt);
        if (input.get_mouse().down(dst::sys::Mouse::Button::Right) ||
            input.get_mouse().down(dst::sys::Mouse::Button::Middle)) {
            cameraPosition.x += input.get_mouse().delta().x * cameraSpeed * dt;
            cameraPosition.y += input.get_mouse().delta().y * cameraSpeed * dt;
        }

        auto view = dst::Matrix4x4::create_view(
            cameraPosition,
            cameraPosition + glm::vec3(0, 0, 1),
            dst::Vector3(0, 1, 0)
        );

        auto projection = dst::Matrix4x4::create_perspective(
            dst::to_radians(fieldOfView),
            window.get_resolution().get_aspect_ratio(),
            0.001f,
            100.0f
        );

        dst_gl(glClearColor(0, 0, 0, 1));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        dst_gl(glViewport(0, 0, window.get_resolution().width, window.get_resolution().height));
        dst_gl(glUseProgram(program.handle));
        dst_gl(glProgramUniformMatrix4fv(program.handle, projectionLocation, 1, GL_FALSE, &projection[0][0]));
        dst_gl(glProgramUniform3fv(program.handle, lightDirectionLocation, 1, &lightDirection.normalized()[0]));
        for (auto& gear : gears) {
            // gear.rotation += gear.speed * clock.elapsed<dst::Second<float>>();
            auto model =
                dst::Matrix4x4::create_rotation(worldRotation) *
                dst::Matrix4x4::create_translation(gear.position) *
                dst::Matrix4x4::create_rotation(
                    dst::Quaternion(gear.rotation, dst::Vector3::UnitZ)
                );

            auto modelView = view * model;
            dst_gl(glProgramUniformMatrix4fv(program.handle, modelViewLocation, 1, GL_FALSE, &modelView[0][0]));
            dst_gl(glProgramUniform4fv(program.handle, colorLocation, 1, &gear.diffuseColor[0]));
            dst_gl(glBindVertexArray(gear.mesh.vertexArray));
            dst_gl(glFrontFace(gear.mesh.winding));
            dst_gl(glPolygonMode(GL_FRONT_AND_BACK, lines ? GL_LINE : GL_FILL));
            dst_gl(glDrawElements(gear.mesh.primitiveType, gear.mesh.indexCount, gear.mesh.indexType, 0));
            dst_gl(glBindVertexArray(0));
        }

        window.swap();
    }

    return 0;
}
