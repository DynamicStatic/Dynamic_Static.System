
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static.System.hpp"

int main()
{
    using namespace dst::sys;
    FMOD::System* fmod = fmod_init();
    while (true) {
        fmod_update(fmod);
    }
    fmod_shutdown(fmod);
    return 0;
}
