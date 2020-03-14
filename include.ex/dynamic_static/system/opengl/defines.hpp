
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/version.hpp"
#include "dynamic_static/system/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

namespace dst {
namespace sys {
namespace gl {

/**
TODO : Documentation
*/
struct Context final
{
    /**
    TODO : Documentation
    */
    struct CreateInfo final
    {
        /**
        TODO : Documentation
        */
        enum class Flags
        {
            DoubleBuffer = 1,                   //!< TODO : Documentation
            VSync        = 1 << 1,              //!< TODO : Documentation
            Default      = DoubleBuffer | VSync //!< TODO : Documentation
        };

        Flags flags { Flags::Default }; //!< TODO : Documentation
        Version version { 4, 5, 0 };    //!< TODO : Documentation
        int depthBits { 24 };           //!< TODO : Documentation
        int stencilBits { 8 };          //!< TODO : Documentation
    };
};

} // namespace gl
} // namespace sys
namespace gl = sys::gl;
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
