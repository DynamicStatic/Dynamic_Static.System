#if 0
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Text/Font.hpp"
#include "Dynamic_Static/System/Defines.hpp"

namespace dst {
namespace sys {
namespace Text {

    /*!
    TODO : Documentation.
    */
    class Layout final
    {
    public:
        struct Info final
        {
            glm::vec2 min { };
            glm::vec2 max { };
            glm::vec2 get_extent() const
            {
                return max - min;
            }
        };

        enum class Alignment
        {

        };

    public:
        glm::vec2 scale { 1, 1 };
        float glyphSpacing { 0 };
        float lineSpacing { 0 };
        dst::Color color { dst::Color::White };
        bool kerningEnabled { true };

    public:
        /*!
        TODO : Documentation.
        */
        template <typename ProcessGlyphFunctionType>
        inline void process(
            const Font& font,
            StringView text,
            ProcessGlyphFunctionType processGlyph,
            Info* pInfo = nullptr
        )
        {
            if (pInfo) {
                auto min = std::numeric_limits<float>::min();
                auto max = std::numeric_limits<float>::max();
                pInfo->min = { max, max };
                pInfo->max = { min, min };
            }
            glm::vec2 cursor { };
            uint16_t vertexIndex = 0;
            std::array<glm::vec2, 4> vertices;
            std::array<glm::vec2, 4> texcoords;
            std::array<uint16_t, 6> indices;
            for (int i = 0; i < text.size(); ++i) {
                const auto& glyph = font[text[i]];
                float w = glyph.width * 0.5f;
                float h = glyph.height * 0.5f;
                float xOffset = glyph.xOffset + w;
                float yOffset = glyph.yOffset + h;
                vertices[0] = cursor + glm::vec2 { -w + xOffset,  h - yOffset } * scale;
                vertices[1] = cursor + glm::vec2 {  w + xOffset,  h - yOffset } * scale;
                vertices[2] = cursor + glm::vec2 {  w + xOffset, -h - yOffset } * scale;
                vertices[3] = cursor + glm::vec2 { -w + xOffset, -h - yOffset } * scale;
                float kerning = 0;
                if (kerningEnabled && i < text.length() - 2) {
                    kerning = font.get_kerning(text[i], text[i + 1]);
                }
                cursor.x += glyph.xAdvance * scale.x + kerning * scale.x + glyphSpacing * scale.x;
                float u = (glyph.width / (float)font.get_image().get_width()) * 0.5f;
                float v = (glyph.height / (float)font.get_image().get_height()) * 0.5f;
                texcoords[0] = glyph.texcoord + glm::vec2 { -u, -v };
                texcoords[1] = glyph.texcoord + glm::vec2 {  u, -v };
                texcoords[2] = glyph.texcoord + glm::vec2 {  u,  v };
                texcoords[3] = glyph.texcoord + glm::vec2 { -u,  v };
                indices[0] = vertexIndex + 0;
                indices[1] = vertexIndex + 1;
                indices[2] = vertexIndex + 2;
                indices[3] = vertexIndex + 0;
                indices[4] = vertexIndex + 2;
                indices[5] = vertexIndex + 3;
                vertexIndex += (uint16_t)vertices.size();
                processGlyph(glyph, color, vertices, texcoords, indices);
                if (pInfo) {
                    pInfo->min.x = std::min(pInfo->min.x, std::min(vertices[0].x, vertices[2].x));
                    pInfo->min.y = std::min(pInfo->min.y, std::min(vertices[0].y, vertices[2].y));
                    pInfo->max.x = std::max(pInfo->max.x, std::max(vertices[0].x, vertices[2].x));
                    pInfo->max.y = std::max(pInfo->max.y, std::max(vertices[0].y, vertices[2].y));
                }
            }
        }

    private:
        void create_layout()
        {

        }

        void adjust_layout()
        {

        }
    };

} // namespace Text
} // namespace sys
} // namespace dst
#endif