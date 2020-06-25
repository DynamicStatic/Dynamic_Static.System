
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
#include "dynamic_static/core/transform.hpp"

namespace rtow {

class Camera final
{
public:
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
    float focalLength { 1.0f };
    dst::Transform transform { };

private:
    glm::vec2 mViewport { };
    glm::vec3 mHorizontal { };
    glm::vec3 mVertical { };
    glm::vec3 mLowerLeftCorner { };
};

} // namespace rtow
