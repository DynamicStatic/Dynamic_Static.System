
# Dynamic_Static.System
Dynamic_Static.System provides easy to use C++ RAII objects for interacting with various input and ouptut systems.  
[GLFW](https://www.glfw.org/) is used for window management and input handling.  
[FMOD](https://www.fmod.com/) is used for audio support.  
[OpenGL](https://www.opengl.org/) is used for graphics support.  
[ImGui](https://github.com/ocornut/imgui) is used for GUI elements.  
[glm](https://glm.g-truc.net/0.9.9/index.html) is used for math.

----------------------------------------------------------------
### Tools

If you're on Windows
  - Download and install [CMake](https://cmake.org/)
  - Download and install [Git and Git Bash](https://git-scm.com/)
  - Download and install [Visual Studio 2017 Community Edition](https://visualstudio.microsoft.com/downloads/)  
  Note that on Windows these instructions assume `Git Bash` (installed with `Git`) is used for command line steps

----------------------------------------------------------------
### Environment
- Create a directory called `Dynamic_Static` wherever is convenient.
- `cd Dynamic_Static/`
- `git clone https://github.com/DynamicStatic/Dynamic_Static.System.git`  

If want to build audio support
- Install [FMOD](https://www.fmod.com/)  
They'll ask you to create an account if you haven't  
FMOD isn't open source, but it's free for non-commercial use  
More info regarding FMOD's license can be found at https://www.fmod.com/licensing

----------------------------------------------------------------
### Build
From your `Dynamic_Static` directory
- `cd Dynamic_Static.System/`
- `git submodule update --init --recursive`
- `mkdir build`
- `cd build/`

If you're on Windows
  - `cmake -G "Visual Studio 15 2017 Win64" ..`
  - Using Windows Explorer, naviagte to `/Dynamic_Static.System/build/`
  - Open `Dynamic_Static.System.sln` with `Visual Studio 2017`
  - From the main menu, select **"Build"**>**"Batch Build..."**
  - Click **"Select All"** then click **"Build"**  

If you're on Ubuntu
  - `cmake ..`
  - `make`

----------------------------------------------------------------
### Run
