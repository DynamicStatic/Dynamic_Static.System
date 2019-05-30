
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static.Core.hpp"
#include "Dynamic_Static.System.hpp"

struct Vtx final
{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec4 color;
};

namespace dst {
namespace sys {
namespace gl {

    template <>
    void enable_vertex_attributes<Vtx>()
    {
        dst::gl::enable_vertex_attributes<Vtx, 3>({{
            { GL_FLOAT, 3 },
            { GL_FLOAT, 2 },
            { GL_FLOAT, 4 }
        }});
    }

} // namespace gl
} // namespace sys
} // namespace dst

int main()
{
    using namespace dst::sys;
    Window::Info windowInfo { };
    windowInfo.name = "Dynamic_Static BasicGui";
    windowInfo.graphicsApi = GraphicsApi::OpenGL;
    windowInfo.resolution.x = 3000;
    windowInfo.glContextInfo.version = { 4, 5 };
    Window window(windowInfo);
    bool running = true;
    window.on_close =
    [&](const Window&)
    {
        running = false;
    };


    dst::sys::Font font;
    font.read_ttf("../../examples/resources/open-sans/OpenSans-Regular.ttf", 64);
    const auto& fontImage = font.get_image();
    fontImage.save_png("../../examples/resources/open-sans/test.png");
    dst::gl::Texture::Info textureInfo { };
    textureInfo.format = GL_RED;
    textureInfo.width = fontImage.get_width();
    textureInfo.height = fontImage.get_height();
    dst::gl::Texture texture(textureInfo, fontImage.get_data().data());

    std::array<dst::gl::Shader, 2> shaders {{
        {
            GL_VERTEX_SHADER,
            __LINE__,
            R"(
                #version 330

                uniform mat4 wvp;
                layout(location = 0) in vec3 vsPosition;
                layout(location = 1) in vec2 vsTexcoord;
                layout(location = 2) in vec4 vsColor;
                out vec2 fsTexcoord;
                out vec4 fsColor;

                void main()
                {
                    gl_Position = wvp * vec4(vsPosition, 1);
                    fsTexcoord = vsTexcoord;
                    fsColor = vsColor;
                }
            )"
        },
        {
            GL_FRAGMENT_SHADER,
            __LINE__,
            R"(
                #version 330

                uniform sampler2D fontTexture;
                in vec2 fsTexcoord;
                in vec4 fsColor;
                out vec4 fragColor;

                void main()
                {
                    fragColor = texture(fontTexture, fsTexcoord).rrrr * fsColor;
                    // fragColor += vec4(1) * 0.25;
                }
            )"
        }
    }};
    dst::gl::Program program(shaders);
    auto wvpLocation = program.get_uniform_location("wvp");

    float scale = 4;
    float uv = 4 / (float)texture.get_info().width;
    auto color = dst::Color::LightGray;
    color.a *= 0.25f;
    std::vector<Vtx> vertices {
        Vtx { glm::vec3 { -1,  1, 0 } * scale, { uv, uv }, color },
        Vtx { glm::vec3 {  1,  1, 0 } * scale, { uv, uv }, color },
        Vtx { glm::vec3 {  1, -1, 0 } * scale, { uv, uv }, color },
        Vtx { glm::vec3 { -1, -1, 0 } * scale, { uv, uv }, color },
    };
    std::vector<uint16_t> indices {
        0, 1, 2,
        0, 2, 3
    };
    dst::gl::Mesh mesh;
    mesh.write<Vtx, uint16_t>(vertices, indices);

    glm::vec3 cameraPosition { 0, 0, 20 };
    float fieldOfView { 40 };

    dst::gl::Mesh textMesh;
    std::vector<Vtx> textVertices;
    std::vector<uint16_t> textIndices;

    dst::sys::Text::Layout layout;

    bool useOffset = true;

    dst::sys::Text::Layout::Info layoutInfo { };

    layout.scale = glm::vec2 { 0.12f, 0.12f };

    dst::sys::Gui gui(std::make_unique<gl::GuiRenderer>());
    dst::Clock clock;
    while (running) {
        clock.update();
        Window::poll_events();
        auto deltaTime = clock.elapsed<dst::Second<float>>();
        const auto& input = window.get_input();
        if (input.keyboard.down(Keyboard::Key::Escape)) {
            running = false;
        }
        if (input.keyboard.pressed(Keyboard::Key::O)) {
            useOffset = !useOffset;
        }
        float cameraSpeed { 7.4f };
        float scrollSensitivity { 86 };
        glm::vec2 lookSensitivity { 1.6f };
        // if (input.mouse.down(Mouse::Button::Left)) {
        //     auto look = input.mouse.get_position_delta() * lookSensitivity * deltaTime;
        //     auto rotationX = glm::angleAxis(look.y, glm::vec3 { 1, 0, 0 });
        //     auto rotationY = glm::angleAxis(look.x, glm::vec3 { 0, 1, 0 });
        //     worldRotation = glm::normalize(rotationX * rotationY * worldRotation);
        // }
        cameraPosition.z -= input.mouse.get_scroll_delta() * scrollSensitivity * deltaTime;
        if (input.mouse.down(Mouse::Button::Middle) ||
            input.mouse.down(Mouse::Button::Right)) {
            cameraPosition.x -= input.mouse.get_position_delta().x * cameraSpeed * deltaTime;
            cameraPosition.y += input.mouse.get_position_delta().y * cameraSpeed * deltaTime;
        }

        glm::ivec2 viewportResolution = window.get_resolution();
        auto viewMatrix = glm::lookAt(
            cameraPosition,
            cameraPosition + glm::vec3 { 0, 0, -1 },
            { 0, 1, 0 }
        );
        auto projectionMatrix = glm::perspective(
            glm::radians(fieldOfView),
            dst::aspect_ratio<glm::ivec2>(viewportResolution),
            0.001f,
            100.0f
        );
        auto wvp = projectionMatrix * viewMatrix;

        dst_gl(glViewport(0, 0, viewportResolution.x, viewportResolution.y));
        dst_gl(glClearColor(0, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        dst_gl(glBindSampler(0, 0));
        dst_gl(glEnable(GL_BLEND));
        dst_gl(glBlendEquation(GL_FUNC_ADD));
        dst_gl(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        dst_gl(glEnable(GL_CULL_FACE));
        dst_gl(glCullFace(GL_BACK));
        // dst_gl(glEnable(GL_DEPTH_TEST));
        program.bind();
        dst_gl(glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]));
        dst_gl(glActiveTexture(GL_TEXTURE0));
        texture.bind();
        mesh.draw_indexed(6);

        ///////////////////////////////////////////////////////////////////////
        static int counter;
        std::string text = "Score : " + std::to_string(counter++);
        textVertices.clear();
        textIndices.clear();
        glm::vec3 offset { -24, 0, 1 };
        layout.process(
            font, text,
            [&](
                const Glyph& glyph,
                const glm::vec4& color,
                const auto& vertices,
                const auto& texcoords,
                const auto& indices
            )
            {
                (void)glyph;
                for (int i = 0; i < 4; ++i) {
                    Vtx vertex;
                    vertex.position.x = vertices[i].x;
                    vertex.position.y = vertices[i].y;
                    vertex.position.z = 0;
                    vertex.texcoord.x = texcoords[i].x;
                    vertex.texcoord.y = texcoords[i].y;
                    vertex.color = color;
                    textVertices.push_back(vertex);
                }
                for (auto index : indices) {
                    textIndices.push_back(index);
                }
            },
            &layoutInfo
        );
        // auto color0 = dst::Color::White;
        // auto color1 = dst::Color::White;
        // for (auto& vertex : textVertices) {
        //     float t = vertex.position.x / layoutInfo.get_extent().x;
        //     vertex.color.r = dst::lerp(color0.r, color1.r, t);
        //     vertex.color.g = dst::lerp(color0.g, color1.g, t);
        //     vertex.color.b = dst::lerp(color0.b, color1.b, t);
        //     vertex.color.a = dst::lerp(color0.a, color1.a, t);
        //     vertex.color *= layout.color;
        //     vertex.position += offset;
        // }

        vertices[0].position.x = layoutInfo.min.x;
        vertices[0].position.y = layoutInfo.max.y;
        vertices[1].position.x = layoutInfo.max.x;
        vertices[1].position.y = layoutInfo.max.y;
        vertices[2].position.x = layoutInfo.max.x;
        vertices[2].position.y = layoutInfo.min.y;
        vertices[3].position.x = layoutInfo.min.x;
        vertices[3].position.y = layoutInfo.min.y;
        mesh.write<Vtx, uint16_t>(vertices, indices);

        textMesh.write<Vtx, uint16_t>(textVertices, textIndices);
        textMesh.draw_indexed((GLsizei)textIndices.size());
        ///////////////////////////////////////////////////////////////////////

        texture.unbind();
        program.unbind();

        gui.begin_frame(clock, window);
        // ImGui::ShowDemoWindow();
        ImGui::SliderFloat("Scale X", &layout.scale.x, 0.1f, 1);
        ImGui::SliderFloat("Scale Y", &layout.scale.y, 0.1f, 1);
        ImGui::SliderFloat("Glyph Spacing", &layout.glyphSpacing, -16, 16);
        ImGui::ColorPicker4("Color", &layout.color[0]);
        ImGui::Checkbox("Kerning Enabled", &layout.kerningEnabled);

        window.make_context_current();
        auto resolution = window.get_resolution();
        // dst_gl(glViewport(0, 0, resolution.x, resolution.y));
        // dst_gl(glClearColor(0, 0, 0, 0));
        // dst_gl(glClear(GL_COLOR_BUFFER_BIT));

        gui.draw();

        window.swap();
    }
    return 0;
}
