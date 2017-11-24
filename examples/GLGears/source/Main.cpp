
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
    dst::Vector3 position;
    dst::Vector3 normal;
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

    void write(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
    {
        dst_gl(glBindVertexArray(vertexArray));
        dst_gl(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        dst_gl(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW));
        dst_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
        dst_gl(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW));
        dst_gl(glEnableVertexAttribArray(0));
        dst_gl(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0));
        dst_gl(glEnableVertexAttribArray(1));
        dst_gl(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(dst::Vector3))));
        dst_gl(glBindBuffer(GL_ARRAY_BUFFER, 0));
        dst_gl(glBindVertexArray(0));

        indexCount = static_cast<GLsizei>(indices.size());
        switch (sizeof(indices[0])) {
            case sizeof(GLubyte) : indexType = GL_UNSIGNED_BYTE; break;
            case sizeof(GLushort) : indexType = GL_UNSIGNED_SHORT; break;
            case sizeof(GLuint) : indexType = GL_UNSIGNED_INT; break;
        }
    }
};

struct Shader final
{
public:
    GLenum stage { 0 };
    GLuint handle { 0 };

public:
    Shader(GLenum stage, const std::string& source)
        : stage { stage }
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
    float speed { 1 };
    float rotation { 0 };
    dst::Color color;
    Mesh mesh;

public:
    Gear(
        float innerRadius,
        float outerRadius,
        float width,
        uint32_t teeth,
        float toothDepth,
        const dst::Vector3& position,
        float speed,
        const dst::Color& color
    )
        : position { position }
        , speed { speed }
        , color { color }
    {
        std::vector<Vertex> vertices;
        auto createVertex =
        [&vertices](const dst::Vector3& position, const dst::Vector3& normal)
        {
            vertices.push_back({ position, normal });
            return static_cast<GLushort>(vertices.size() - 1);
        };

        std::vector<GLushort> indices;
        auto createFace =
        [&indices](const std::array<GLushort, 3>& face)
        {
            std::copy_n(face.begin(), face.size(), std::back_inserter(indices));
        };

        const dst::Vector3 w(0, 0, width * 0.5f);
        const float pi = static_cast<float>(M_PI);
        const float ta = 2.0f * pi / teeth;
        const float da = ta / 4;
        for (uint32_t tooth_i = 0; tooth_i < teeth; ++tooth_i) {
            float a = ta * tooth_i;
            std::array<dst::Vector3, 5> anchors;
            for (size_t anchor_i = 0; anchor_i < anchors.size(); ++anchor_i) {
                anchors[anchor_i].x = cos(a + da * anchor_i);
                anchors[anchor_i].y = sin(a + da * anchor_i);
            }

            // Front face
            auto normal = dst::Vector3::UnitZ;
            auto i0 = createVertex(anchors[0] * outerRadius + w, normal);
            auto i1 = createVertex(anchors[3] * outerRadius + w, normal);
            auto i2 = createVertex(anchors[4] * innerRadius + w, normal);
            auto i3 = createVertex(anchors[0] * innerRadius + w, normal);
            auto i4 = createVertex(anchors[4] * outerRadius + w, normal);
            createFace({ i0, i1, i2 });
            createFace({ i0, i2, i3 });
            createFace({ i1, i4, i2 });

            // Tooth front face
            normal = dst::Vector3::UnitZ;
            i0 = createVertex(anchors[1] * (outerRadius + toothDepth) + w, normal);
            i1 = createVertex(anchors[2] * (outerRadius + toothDepth) + w, normal);
            i2 = createVertex(anchors[3] *  outerRadius +               w, normal);
            i3 = createVertex(anchors[0] *  outerRadius +               w, normal);
            createFace({ i0, i1, i2 });
            createFace({ i0, i2, i3 });
        }
        
        vertices.push_back({ {  0,     0.5f, 0 }, dst::Vector3::One });
        vertices.push_back({ { -0.5f, -0.5f, 0 }, dst::Vector3::One });
        vertices.push_back({ { -0.5f, -0.5f, 0 }, dst::Vector3::One });
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
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
        Gear(0.2f, 1.0f, 4.0f, 4, 0.5f, { -3.0f,  0.0f, 0.0f },  1, dst::Color::Red),
        Gear(0.5f, 2.0f, 2.0f, 10, 0.7f, {  3.1f,  0.0f, 0.0f }, -2, dst::Color::Green),
        Gear(1.3f, 2.0f, 0.5f, 10, 0.7f, { -3.1f, -6.2f, 0.0f }, -2, dst::Color::Blue)
    };

    Program program(
        R"(
            #version 330
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            layout(location = 0) in vec3 vsPosition;
            layout(location = 1) in vec3 vsNormal;
            out vec3 fsNormal;
            void main()
            {
                mat4 modelView = view * model;
                vec4 position = modelView * vec4(vsPosition, 1);
                gl_Position = projection * position;
            }
        )",
        R"(
            #version 330
            uniform vec4 color;
            in vec3 fsNormal;
            out vec4 fragColor;
            void main()
            {
                fragColor = color;
            }
        )"
    );

    GLint modelLocation;
    GLint viewLocation;
    GLint projectionLocation;
    GLint colorLocation;
    dst_gl(modelLocation = glGetUniformLocation(program.handle, "model"));
    dst_gl(viewLocation = glGetUniformLocation(program.handle, "view"));
    dst_gl(projectionLocation = glGetUniformLocation(program.handle, "projection"));
    dst_gl(colorLocation = glGetUniformLocation(program.handle, "color"));

    bool lines = false;
    float zoom = -16;
    float zoomSpeed = 12;

    dst::Clock clock;
    bool running = true;
    while (running) {
        clock.update();
        dst::sys::Window::update();
        const auto& input = window.get_input();
        if (input.get_keyboard().down(dst::sys::Keyboard::Key::Escape)) {
            running = false;
        }

        if (input.get_keyboard().pressed(dst::sys::Keyboard::Key::Tab)) {
            lines = !lines;
        }

        zoom += static_cast<float>(input.get_mouse().scroll() * zoomSpeed * clock.elapsed<dst::Second<>>());




        auto view = dst::Matrix4x4::create_view(
            dst::Vector3(0, 0, zoom),
            dst::Vector3(-1, -1.5f, 0),
            dst::Vector3::Up
        );

        auto projection = dst::Matrix4x4::create_perspective(
            dst::to_radians(60.0f),
            window.get_resolution().get_aspect_ratio(),
            0.001f,
            100.0f
        );

        dst_gl(glClearColor(0.25f, 0.25f, 0.25f, 1));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT));
        dst_gl(glViewport(0, 0, window.get_resolution().width, window.get_resolution().height));
        dst_gl(glUseProgram(program.handle));
        dst_gl(glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]));
        dst_gl(glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]));
        for (auto& gear : gears) {
            // gear.rotation += gear.speed * clock.elapsed<dst::Second<float>>();
            auto model =
                dst::Matrix4x4::create_translation(gear.position) *
                dst::Matrix4x4::create_rotation(
                    dst::Quaternion(gear.rotation, dst::Vector3::UnitZ)
                );

            dst_gl(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]));
            dst_gl(glProgramUniform4fv(program.handle, colorLocation, 1, &gear.color[0]));
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
