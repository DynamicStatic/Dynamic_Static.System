
# Dynamic_Static.System
----------------------------------------------------------------
### Get Tools
* [Git](https://git-scm.com/)
* [CMake](https://cmake.org/)
* [Visual Studio 2017 Community Edition](https://visualstudio.microsoft.com/downloads/)  
Note that on Windows these instructions assume `Git Bash` (installed with `Git`) is used for command line steps
  
----------------------------------------------------------------
### Setup Environment
* Create a directory called `Dynamic_Static` wherever is convenient.
* `cd Dynamic_Static/`
* `git clone https://github.com/DynamicStatic/Dynamic_Static.System.git`  

If you're building `Dynamic_Static.Audio`  
  - Register and install [FMOD](https://www.fmod.com/)  
  - FMOD isn't open source, but it's free for non-commercial use.  
  - More info regarding FMOD's license can be found at https://www.fmod.com/licensing

If you're building the `Dynamic_Static.SDK`  
  - Create an environment variable called `DYNAMIC_STATIC_SDK` and point it to your `Dynamic_Static` directory.

----------------------------------------------------------------
### Build

Create a directory called `Dynamic_Static` wherever is convenient.  
* `cd Dynamic_Static.System/`
