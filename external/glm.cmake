
#==========================================
#  Copyright (c) 2016-2018 Dynamic_Static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

set(glm.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/glm/")
file(GLOB glm.clutter "${glm.includeDirectories}/*")
list(REMOVE_ITEM glm.clutter "${glm.includeDirectories}/glm")
list(APPEND glm.clutter "${glm.includeDirectories}/glm/CMakeLists.txt")
file(REMOVE_RECURSE ${glm.clutter})
