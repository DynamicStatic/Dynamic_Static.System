
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#ifdef DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
#include "Dynamic_Static/System/OpenGL.hpp"
#endif
#include "GLFW/glfw3.h"
#ifdef DYNAMIC_STATIC_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined DYNAMIC_STATIC_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#include "GLFW/glfw3native.h"

namespace Dynamic_Static {
namespace System {
namespace detail {

    /*
    * Gets the last GLFW error message for the calling thread.
    * @return The last GLFW error message for the calling thread
    */
    static inline std::string& get_last_glfw_error_message()
    {
        thread_local std::string tlErrorMessage;
        return tlErrorMessage;
    }

    /*
    * Function used for handling errors reported from GLFW.
    * @param [in] error The GLFW error code for the current error
    * @param [in] desctiption The GLFW error description
    */
    static inline void glfw_error_callback(int error, const char* description)
    {
        auto& lastErrorMessage = get_last_glfw_error_message();
        lastErrorMessage = "GLFW Error " + std::to_string(error) + " : " + std::string(description);
        // TODO : Setup logger in dst::core.
        std::cerr << lastErrorMessage << std::endl;
    }

} // namespace detail
} // namespace System
} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_SYSTEM_GLFW_ENABLED
