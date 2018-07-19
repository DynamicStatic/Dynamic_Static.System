
#if defined(DYNAMIC_STATIC_GLFW_ENABLED)
namespace Dynamic_Static {
namespace System {
namespace detail {

    template <typename FunctionType>
    inline void access_glfw_window_handles(FunctionType accessFunction)
    {
        static std::mutex sMutex;
        static std::set<GLFWwindow*> sGlfwWindowHandles;
        std::lock_guard<std::mutex> lock(sMutex);
        accessFunction(sGlfwWindowHandles);
    }

    inline void glfw_error_callback(int error, const char* description)
    {

    }

} // namespace detail

    class Window final
        : detail::Window
    {
    public:
        typedef detail::Window::Info Info;

    private:
        GLFWwindow* mGlfwWindow { nullptr };

    public:
        /*
        * Constructs an instance of Window.
        * @param [in] configuration This Window's Configuration (optional = default Configuration)
        */
        Window(const Info& info)
        {

        }

        /*
        * Destroys this instance of Window.
        */
        inline ~Window()
        {

        }

    public:
        inline GLFWwindow* get_glfw_window() const
        {
            return mGlfwWindow;
        }
    };

    inline Window::Window(const Info& info)
    {
        detail::access_glfw_window_handles(
            [&](std::set<GLFWwindow*>& glfwWindowHandles)
            {
                if (glfwWindowHandles.empty()) {
                    glfwSetErrorCallback(detail::glfw_error_callback);
                    if (glfwInit() == GLFW_FALSE) {
                        // TODO : Error message
                        throw std::runtime_error("GLFW failed to initialize");
                    }

                    switch (info.graphicsApi) {
                        #if defined(DYNAMIC_STATIC_OPENGL_ENABLED)
                        case GraphicsApi::OpenGL:
                        {
                            // TODO : Can this be removed on all platforms?
                            // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.openGlContextInfo.version.major);
                            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.openGlContextInfo.version.minor);
                            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                        } break;
                        #endif

                        default: glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); break;
                    }
                }

                glfwWindowHint(GLFW_VISIBLE, info.visible);
                glfwWindowHint(GLFW_DECORATED, info.decorated);
                glfwWindowHint(GLFW_RESIZABLE, info.resizable);

                // TODO : Parent Window
                // TODO : Monitor
                // TODO : GLFWwindow handle is not OS window handle...clarify names
                GLFWwindow* parent = info.parent->get_glfw_window();
            }
        );
    }

    inline void Window::move(Window&& other)
    {
        mGlfwWindow = std::move(other.mGlfwWindow);
        other.mGlfwWindow = nullptr;
    }

} // namespace System
} // namespace Dynamic_Static
#endif
