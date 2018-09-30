
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static.Core.hpp"
#include "Dynamic_Static.System.hpp"

int main()
{

    dst::sys::Font font;
    font.read_ttf("../../examples/resources/open-sans/OpenSans-Regular.ttf", 64);
    font.get_image().save_png("../../examples/resources/open-sans/test.png");
    return 0;
}
