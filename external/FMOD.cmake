
# ==========================================
#   Copyright (c) 2018-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(programFiles "$ENV{PROGRAMFILES} (x86)")
set(FMOD.installDirectory "${programFiles}/FMOD SoundSystem/FMOD Studio API Windows/")
set(FMOD.apiDirectory "${FMOD.installDirectory}/api/")

set(FMOD.fsbank.includeDirectory "${FMOD.apiDirectory}/fsbank/inc/")
set(FMOD.fsbank.libraryDirectory "${FMOD.apiDirectory}/fsbank/lib/")

set(FMOD.lowlevel.includeDirectory "${FMOD.apiDirectory}/lowlevel/inc/")
set(FMOD.lowlevel.libraryDirectory "${FMOD.apiDirectory}/lowlevel/lib/")

set(FMOD.studio.includeDirectory "${FMOD.apiDirectory}/studio/inc/")
set(FMOD.studio.libraryDirectory "${FMOD.apiDirectory}/studio/lib/")

set(FMOD.includeDirectories
    ${FMOD.fsbank.includeDirectory}
    ${FMOD.lowlevel.includeDirectory}
    ${FMOD.studio.includeDirectory}
)

set(FMOD.staticLibraries
    ${FMOD.fsbank.libraryDirectory}/fsbank64_vc.lib
    ${FMOD.lowlevel.libraryDirectory}/fmod64_vc.lib
    ${FMOD.studio.libraryDirectory}/fmodstudio64_vc.lib
)

set(FMOD.sharedLibraries
    ${FMOD.fsbank.libraryDirectory}/fsbank64.dll
    ${FMOD.lowlevel.libraryDirectory}/fmod64.dll
    ${FMOD.studio.libraryDirectory}/fmodstudio64.dll
)
