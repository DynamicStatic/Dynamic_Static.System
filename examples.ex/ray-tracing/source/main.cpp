
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static.core.hpp"
#include "dynamic_static.system.hpp"

#include <array>
#include <vector>

namespace dst {
namespace sys {
namespace gl {

template <>
inline void enable_vertex_attributes<glm::vec2>()
{
    enable_vertex_attributes<glm::vec2, 3>({ {
        { GL_FLOAT, 2 },
    } });
}

} // namespace gl
} // namespace sys
} // namespace dst

class RayTracer final
{
public:
    inline RayTracer(const glm::vec2& viewport)
    {
        using namespace dst::gl;
        std::array<glm::vec2, 3> vertices {
            glm::vec2 { -1, -1 },
            glm::vec2 { -1,  3 },
            glm::vec2 {  3, -1 },
        };
        std::array<GLushort, 3> indices { 0, 1, 2 };
        auto s = sizeof(GLushort);
        mMesh.write<glm::vec2, GLushort>(
            { vertices.data(), vertices.size() },
            { indices.data(), indices.size() }
        );
        Texture::Info textureInfo { };
        textureInfo.format = GL_RGBA;
        textureInfo.width = (GLsizei)viewport.x;
        textureInfo.height = (GLsizei)viewport.y;
        textureInfo.storageType = GL_FLOAT;
        mTexture = Texture(textureInfo);
        mPixels.resize((size_t)textureInfo.width * (size_t)textureInfo.height);
        std::array<Shader, 2> shaders {{
            {
                GL_VERTEX_SHADER,
                __LINE__,
                R"(
                    #version 330
                    layout(location = 0) in vec2 vsPosition;
                    out vec2 fsTexCoord;
                    void main()
                    {
                        fsTexCoord = vsPosition;
                        gl_Position = vec4(vsPosition, 0, 1);
                    }
                )"
            },
            {
                GL_FRAGMENT_SHADER,
                __LINE__,
                R"(
                    #version 330
                    uniform sampler2D image;
                    in vec2 fsTexCoord;
                    out vec4 fragColor;
                    void main()
                    {
                        fragColor = texture(image, fsTexCoord);
                        fragColor.a = 1;
                    }
                )"
            }
        }};
        mProgram = Program(shaders);
        mTextureLocation = mProgram.uniform_location("image");
    }

    inline void update(const dst::sys::Input& input)
    {
        for (auto& pixel : mPixels) {
            pixel.r = 1.0f;
            pixel.b = 1.0f;
        }
    }

    inline void draw(const glm::vec2& viewport)
    {
        mTexture.write((const uint8_t*)mPixels.data());
        dst_gl(glDisable(GL_CULL_FACE));
        dst_gl(glDisable(GL_DEPTH_TEST));
        dst_gl(glDisable(GL_SCISSOR_TEST));
        dst_gl(glClearColor(1, 0, 0, 0));
        dst_gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        dst_gl(glViewport(0, 0, (GLsizei)viewport.x, (GLsizei)viewport.y));
        mProgram.bind();
        dst_gl(glBindSampler(0, 0));
        dst_gl(glActiveTexture(GL_TEXTURE0));
        mTexture.bind();
        mMesh.draw_indexed();
        mProgram.unbind();
    }

private:
    dst::gl::Mesh mMesh;
    dst::gl::Texture mTexture;
    std::vector<glm::vec4> mPixels;
    dst::gl::Program mProgram;
    GLuint mTextureLocation { 0 };
};

int main(int argc, char* argv[])
{
    using namespace dst::sys;
    Window::Info windowInfo { };
    windowInfo.pName = "Dynamic_Static GL Gears";
    windowInfo.graphicsApi = GraphicsApi::OpenGL;
    windowInfo.glContextInfo.version = { 4, 5 };
    Window window(windowInfo);
    bool closeRequested = false;
    window.on_close_requested =
        [&](const Window&)
    {
        closeRequested = true;
    };

    gl::Gui gui;
    RayTracer rayTracer(window.info().extent);
    dst::Clock clock;
    while (!closeRequested && !window.input().keyboard.down(Keyboard::Key::Escape)) {
        clock.update();
        Window::poll_events();
        gui.begin_frame(clock, window);
        // ImGui::Checkbox("Animation", &renderer.animation);
        // ImGui::Checkbox("Wireframe", &renderer.wireFrame);
        auto& input = window.input();
        if (ImGui::GetIO().WantCaptureMouse) {
            input.revert();
        }
        rayTracer.update(window.input());
        rayTracer.draw(window.info().extent);
        gui.end_frame();
        gui.draw();
        window.swap();
    }
    return 0;
}
