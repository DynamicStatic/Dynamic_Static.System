
# Dynamic_Static.System
Dynamic_Static.System provides easy to use C++ RAII  objects for interacting with various input and ouptut systems.  
Window management and input handling are provided using [GLFW](https://www.glfw.org/).  
Audio support is provided using [FMOD](https://www.fmod.com/).  
GUI controls are provided using [ImGui](https://github.com/ocornut/imgui).  
Basic graphics support is provided using [OpenGL](https://www.opengl.org/).  

----------------------------------------------------------------
### Get Tools
- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- [Visual Studio 2017 Community Edition](https://visualstudio.microsoft.com/downloads/)  
Note that on Windows these instructions assume `Git Bash` (installed with `Git`) is used for command line steps

----------------------------------------------------------------
### Setup Environment
- Create a directory called `Dynamic_Static` wherever is convenient.
- `cd Dynamic_Static/`
- `git clone https://github.com/DynamicStatic/Dynamic_Static.System.git`  

If you're building `Dynamic_Static.Audio`  
- Install [FMOD](https://www.fmod.com/)  
They'll ask you to create an account if you haven't  
FMOD isn't open source, but it's free for non-commercial use.  
More info regarding FMOD's license can be found at https://www.fmod.com/licensing

----------------------------------------------------------------
### Build
- From your `Dynamic_Static` directory...
- `cd Dynamic_Static.System/`
