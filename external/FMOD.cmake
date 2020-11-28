
#### # ==========================================
#### #   Copyright (c) 2018-2020 Dynamic_Static
#### #     Patrick Purcell
#### #       Licensed under the MIT license
#### #     http://opensource.org/licenses/MIT
#### # ==========================================
#### 
#### if(MSVC)
####     get_filename_component(
####         FMOD.apiDirectory
####         "[HKEY_CURRENT_USER\\Software\\FMOD Studio API Windows]"
####         ABSOLUTE CACHE
####     )
####     set(FMOD.apiDirectory "${FMOD.apiDirectory}/api/")
####     string(REPLACE "\\" "/" FMOD.apiDirectory "${FMOD.apiDirectory}")
#### endif()
#### if(EXISTS ${FMOD.apiDirectory})
####     set(FMOD.available True)
####     set(FMOD.fsbank.includeDirectory "${FMOD.apiDirectory}/fsbank/inc/")
####     set(FMOD.lowlevel.includeDirectory "${FMOD.apiDirectory}/lowlevel/inc/")
####     set(FMOD.studio.includeDirectory "${FMOD.apiDirectory}/studio/inc/")
####     set(FMOD.includeDirectories
####         "${FMOD.fsbank.includeDirectory}"
####         "${FMOD.lowlevel.includeDirectory}"
####         "${FMOD.studio.includeDirectory}"
####     )
####     set(FMOD.fsbank.libraryDirectory "${FMOD.apiDirectory}/fsbank/lib/")
####     set(FMOD.lowlevel.libraryDirectory "${FMOD.apiDirectory}/lowlevel/lib/")
####     set(FMOD.studio.libraryDirectory "${FMOD.apiDirectory}/studio/lib/")
####     set(FMOD.staticLibraries
####         "${FMOD.fsbank.libraryDirectory}/fsbank64_vc.lib"
####         "${FMOD.lowlevel.libraryDirectory}/fmod64_vc.lib"
####         "${FMOD.studio.libraryDirectory}/fmodstudio64_vc.lib"
####     )
####     set(FMOD.sharedLibraries
####         "${FMOD.fsbank.libraryDirectory}/fsbank64.dll"
####         "${FMOD.lowlevel.libraryDirectory}/fmod64.dll"
####         "${FMOD.studio.libraryDirectory}/fmodstudio64.dll"
####     )
#### endif()
