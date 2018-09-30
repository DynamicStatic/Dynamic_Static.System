
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Text/Font.hpp"

#ifndef STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#endif
#include "stb_truetype.h"

#include <algorithm>
#include <fstream>
#include <memory>

namespace dst {

    template <typename T>
    class Atlas final
    {
    public:
        struct CreateInfo final
        {
        };

        struct Rectangle final
        {
            int x;
            int y;
            int width;
            int height;
            int get_top() const { return y; }
            int get_left() const { return x; }
            int get_right() const { return x + width; }
            int get_bottom() const { return y + height; }
            int get_area() const { return width * height; }
        };

        struct Entry final
        {
            Rectangle rectangle { };
            int page { 0 };
            T data { };
        };

    private:
        struct Node final
        {
            Rectangle rectangle { };
            Node* left { nullptr };
            Node* right { nullptr };
            Node* overflow { nullptr };
            bool occupied { false };
            Node* insert(Atlas<T>& atlas, Entry& entry)
            {
                Node* node = nullptr;
                if (left || right) {
                    bool insertLeft = left->rectangle.get_area() < right->rectangle.get_area();
                    node = insertLeft ? left->insert(atlas, entry) : right->insert(atlas, entry);
                    if (!node) {
                        node = insertLeft ? right->insert(atlas, entry) : left->insert(atlas, entry);
                    }
                } else {
                    if (!occupied &&
                        rectangle.width >= entry.rectangle.width &&
                        rectangle.height >= entry.rectangle.height) {
                        left = atlas.create_node();
                        right = atlas.create_node();

                        left->rectangle.x = rectangle.get_left();
                        left->rectangle.y = rectangle.get_top() + entry.rectangle.height;
                        left->rectangle.width = rectangle.width;
                        left->rectangle.height = rectangle.height - entry.rectangle.height;

                        right->rectangle.x = rectangle.get_left() + entry.rectangle.width;
                        right->rectangle.y = rectangle.get_top();
                        right->rectangle.width = rectangle.width - entry.rectangle.width;
                        right->rectangle.height = entry.rectangle.height;

                        entry.rectangle.x = rectangle.x;
                        entry.rectangle.y = rectangle.y;
                        occupied = true;
                        node = this;
                    }
                }
                return node;
            }
        };

    private:
        std::vector<std::unique_ptr<Node>> mNodes;
        int mWidth { 1024 };
        int mHeight { 1024 };
        int mPageCount { 1 };
        int mPadding { 2 };

    public:
        Atlas(Span<Entry> entries)
        {
            std::sort(
                entries.begin(), entries.end(),
                [](const Entry& lhs, const Entry& rhs)
                {
                    if (lhs.rectangle.height == rhs.rectangle.height) {
                        return lhs.rectangle.width > rhs.rectangle.width;
                    } else {
                        return lhs.rectangle.height > rhs.rectangle.height;
                    }
                }
            );

            auto padding = mPadding * 2;
            for (auto& entry : entries) {
                entry.rectangle.width += padding;
                entry.rectangle.height += padding;
            }
            auto root = create_node();
            root->rectangle.width = mWidth;
            root->rectangle.height = mHeight;
            for (auto& entry : entries) {
                if (!root->insert(*this, entry)) {
                    int page = 0;
                    auto node = root;
                    while (node->overflow) {
                        node = node->overflow;
                        ++page;
                    }
                    if (!node->insert(*this, entry)) {
                        ++page;
                        node->overflow = create_node();
                        node->overflow->rectangle.width = mWidth;
                        node->overflow->rectangle.height = mHeight;
                        node->overflow->insert(*this, entry);
                        ++mPageCount;
                    }
                    entry.page = page;
                }
            }
            for (auto& entry : entries) {
                entry.rectangle.width -= padding;
                entry.rectangle.height -= padding;
            }
            mNodes.clear();
        }

    public:
        int get_width() const { return mWidth; }
        int get_height() const { return mHeight; }
        int get_page_count() const { return mPageCount; }
        int get_padding() const { return mPadding; }

    private:
        Node* create_node()
        {
            // TODO : "scratch pad" storage...
            mNodes.push_back(std::make_unique<Node>());
            return mNodes.back().get();
        }
    };

} // namespace dst

namespace dst {
namespace sys {

    float Font::get_ascent() const { return mAscent; }
    float Font::get_descent() const { return mDescent; }
    float Font::get_line_gap() const { return mLineGap; }
    const Image& Font::get_image() const { return mImage; }

    void Font::read_ttf(
        const dst::StringView filePath,
        float lineHeight,
        const dst::StringView characters
    )
    {
        // TODO : Need to remove duplicate characters.
        // TODO : "scratch pad" storage...
        auto ttfBytes = dst::File::read_all_bytes(filePath);
        stbtt_fontinfo fontInfo { };
        if (stbtt_InitFont(&fontInfo, (const unsigned char*)ttfBytes.data(), 0)) {
            auto scale = stbtt_ScaleForPixelHeight(&fontInfo, lineHeight);
            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
            mAscent = ascent * scale;
            mDescent = descent * scale;
            mLineGap = lineGap * scale;

            std::vector<Atlas<char>::Entry> atlasEntries;
            atlasEntries.reserve(characters.size());
            for (auto character : characters) {
                glm::ivec2 v0;
                glm::ivec2 v1;
                stbtt_GetCodepointBitmapBox(&fontInfo, character, scale, scale, &v0.x, &v0.y, &v1.x, &v1.y);
                Atlas<char>::Entry atlasEntry { };
                atlasEntry.rectangle.width = v1.x - v0.x;
                atlasEntry.rectangle.height = v1.y - v0.y;
                atlasEntry.data = character;
                atlasEntries.push_back(atlasEntry);
            }
            Atlas<char> atlas(atlasEntries);
            mImage = Image(atlas.get_width(), atlas.get_height());
            for (auto atlasEntry : atlasEntries) {
                auto rectangle = atlasEntry.rectangle;
                stbtt_MakeCodepointBitmap(
                    &fontInfo,
                    &mImage[glm::ivec2 { rectangle.x + 2, rectangle.y + 2 }],
                    rectangle.width,
                    rectangle.height,
                    mImage.get_width(),
                    scale,
                    scale,
                    atlasEntry.data
                );
            }
            int breaker = 0;
        }
    }

} // namespace sys
} // namespace dst
