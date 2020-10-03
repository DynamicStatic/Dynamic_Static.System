
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

#include "ray.hpp"

#include "dynamic_static/core/math.hpp"
#include "dynamic_static/core/time.hpp"
#include "dynamic_static/core/transform.hpp"
#include "dynamic_static/system/input.hpp"

namespace rtow {

class Camera final
{
public:
    inline void update(const dst::Clock& clock, const dst::sys::Input& input)
    {
        using namespace dst::sys;
        auto deltaTime = clock.elapsed<dst::Seconds<float>>();
        if (moveEnabled) {
            glm::vec3 direction { };
            direction += input.keyboard.down(Keyboard::Key::Q) ? transform.up() : glm::vec3 { };
            direction += input.keyboard.down(Keyboard::Key::E) ? transform.down() : glm::vec3 { };
            direction += input.keyboard.down(Keyboard::Key::A) ? transform.left() : glm::vec3 { };
            direction += input.keyboard.down(Keyboard::Key::D) ? transform.right() : glm::vec3 { };
            direction += input.keyboard.down(Keyboard::Key::W) ? transform.forward() : glm::vec3 { };
            direction += input.keyboard.down(Keyboard::Key::S) ? transform.backward() : glm::vec3 { };
            if (direction.x || direction.y || direction.z) {
                direction = glm::normalize(direction);
            }
            transform.translation += direction * speed * deltaTime;
        }
        if (lookEnabled) {
            float verticalLookMax = glm::radians(90.0f);
            auto look = input.mouse.position_delta() * sensitivity * deltaTime;
            if (verticalLookMax < mVerticalLook + look.y) {
                look.y = verticalLookMax - mVerticalLook;
            } else
            if (mVerticalLook + look.y < -verticalLookMax) {
                look.y = -verticalLookMax - mVerticalLook;
            }
            mVerticalLook += look.y;
            auto rotationX = glm::angleAxis(-look.y, glm::vec3 { 1, 0, 0 });
            auto rotationY = glm::angleAxis(-look.x, glm::vec3 { 0, 1, 0 });
            transform.rotation = glm::normalize(rotationY * transform.rotation * rotationX);
        }
    }

    inline glm::mat4 view() const
    {
        return glm::lookAt(
            transform.translation,
            transform.translation + transform.forward(),
            transform.up()
        );
    }

    inline glm::mat4 projection() const
    {
        return glm::perspective(
            glm::radians(fieldOfView),
            16.0f / 9.0f,
            0.001f,
            100.0f
        );
    }

    inline void update()
    {
        mViewport.y = 2.0f;
        mViewport.x = mViewport.y * dst::aspect_ratio(extent);
        mHorizontal = glm::vec3(mViewport.x, 0.0f, 0.0f);
        mVertical = glm::vec3(0.0f, mViewport.y, 0.0f);
        mLowerLeftCorner = transform.translation - mHorizontal * 0.5f - mVertical * 0.5f - glm::vec3(0.0f, 0.0f, focalLength);
    }

    inline Ray get_ray(const glm::vec2& texCoord) const
    {
        return Ray { transform.translation, mLowerLeftCorner + texCoord.x * mHorizontal + texCoord.y * mVertical - transform.translation };
    }

    glm::uvec2 extent { };
    float fieldOfView { 40.0f };
    float focalLength { 1.0f };
    dst::Transform transform { };

    bool moveEnabled { true };
    bool lookEnabled { true };
    float speed { 4.2f };
    glm::vec2 sensitivity { 2.0f, 2.0f };

private:
    glm::vec2 mViewport { };
    glm::vec3 mHorizontal { };
    glm::vec3 mVertical { };
    glm::vec3 mLowerLeftCorner { };

    float mVerticalLook { };
};

} // namespace rtow
