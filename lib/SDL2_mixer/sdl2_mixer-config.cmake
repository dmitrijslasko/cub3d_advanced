# sdl2_mixer cmake project-config input for ./configure scripts

include(FeatureSummary)
set_package_properties(SDL2_mixer PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_mixer/"
    DESCRIPTION "SDL_mixer is a sample multi-channel audio mixer library"
)

set(SDL2_mixer_FOUND                TRUE)

set(SDL2MIXER_VENDORED              0)

set(SDL2MIXER_CMD                   1)

set(SDL2MIXER_FLAC_LIBFLAC          0)
set(SDL2MIXER_FLAC_DRFLAC           1)
if(SDL2MIXER_FLAC_LIBFLAC OR SDL2MIXER_FLAC_DRFLAC)
    set(SDL2MIXER_FLAC              1)
else()
    set(SDL2MIXER_FLAC              0)
endif()

set(SDL2MIXER_GME                   0)

set(SDL2MIXER_MOD_MODPLUG           0)
set(SDL2MIXER_MOD_XMP               0)
set(SDL2MIXER_MOD_XMP_LITE          0)
if(SDL2MIXER_MOD_MODPLUG OR SDL2MIXER_MOD_XMP OR SDL2MIXER_MOD_XMP_LITE)
    set(SDL2MIXER_MOD               1)
else()
    set(SDL2MIXER_MOD               0)
endif()

set(SDL2MIXER_MP3_MINIMP3           1)
set(SDL2MIXER_MP3_MPG123            0)
if(SDL2MIXER_MP3_MINIMP3 OR SDL2MIXER_MP3_MPG123)
    set(SDL2MIXER_MP3               1)
else()
    set(SDL2MIXER_MP3               0)
endif()

set(SDL2MIXER_MIDI_FLUIDSYNTH       0)
set(SDL2MIXER_MIDI_NATIVE           0)
set(SDL2MIXER_MIDI_TIMIDITY         1)
if(SDL2MIXER_MIDI_FLUIDSYNTH OR SDL2MIXER_MIDI_NATIVE OR SDL2MIXER_MIDI_TIMIDITY)
    set(SDL2MIXER_MIDI              1)
else()
    set(SDL2MIXER_MIDI              0)
endif()

set(SDL2MIXER_OPUS                  0)

set(SDL2MIXER_VORBIS)
set(SDL2MIXER_VORBIS_STB            1)
set(SDL2MIXER_VORBIS_VORBISFILE     0)
set(SDL2MIXER_VORBIS_TREMOR         0)
if(SDL2MIXER_VORBIS_STB)
    set(SDL2MIXER_VORBIS            STB)
endif()
if(SDL2MIXER_VORBIS_VORBISFILE)
    set(SDL2MIXER_VORBIS            VORBISFILE)
endif()
if(SDL2MIXER_VORBIS_TREMOR)
    set(SDL2MIXER_VORBIS            TREMOR)
endif()

set(SDL2MIXER_WAVE                  1)

set(SDL2MIXER_WAVPACK               0)

set(SDL2MIXER_SDL2_REQUIRED_VERSION 2.0.9)

get_filename_component(CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR} REALPATH)
get_filename_component(prefix "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)
set(exec_prefix "${prefix}")
set(bindir "${exec_prefix}/bin")
set(includedir "${prefix}/include")
set(libdir "${exec_prefix}/lib")
set(_sdl2mixer_extra_static_libraries ";m")
string(REGEX REPLACE "(^[;]+|[;]+$)" "" _sdl2mixer_extra_static_libraries "${_sdl2mixer_extra_static_libraries}")

set(_sdl2mixer_bindir   "${bindir}")
set(_sdl2mixer_libdir   "${libdir}")
set(_sdl2mixer_incdir   "${includedir}/SDL2")

include(CMakeFindDependencyMacro)

set(_original_cmake_module_path "${CMAKE_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

include("${CMAKE_CURRENT_LIST_DIR}/PkgConfigHelper.cmake")

if("modplug::modplug" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(modplug)
endif()

if("libxmp::libxmp" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(libxmp)
endif()

if("libxmp-lite::libxmp-lite" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(libxmp-lite)
endif()

if("FluidSynth::libfluidsynth" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(FluidSynth)
endif()

if("Vorbis::vorbisfile" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(Vorbis)
endif()

if("tremor::tremor" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(tremor)
endif()

if("FLAC::FLAC" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(FLAC)
endif()

if("MPG123::libmpg123" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(mpg123)
endif()

if("OpusFile::opusfile" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(OpusFile)
endif()

if("WavPack::WavPack" IN_LIST _sdl2mixer_extra_static_libraries)
    find_dependency(wavpack)
endif()

set(CMAKE_MODULE_PATH "${_original_cmake_module_path}")
unset(_original_cmake_module_path)

unset(prefix)
unset(exec_prefix)
unset(bindir)
unset(includedir)
unset(libdir)

include(CMakeFindDependencyMacro)

if(NOT TARGET SDL2_mixer::SDL2_mixer)
    if(WIN32)
        set(_sdl2mixer_dll "${_sdl2mixer_bindir}/SDL2_mixer.dll")
        set(_sdl2mixer_imp "${_sdl2mixer_libdir}/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer.dll${CMAKE_STATIC_LIBRARY_SUFFIX}")
        if(EXISTS "${_sdl2mixer_dll}" AND EXISTS "${_sdl2mixer_imp}")
            add_library(SDL2_mixer::SDL2_mixer SHARED IMPORTED)
            set_target_properties(SDL2_mixer::SDL2_mixer
                PROPERTIES
                    IMPORTED_LOCATION "${_sdl2mixer_dll}"
                    IMPORTED_IMPLIB "${_sdl2mixer_imp}"
            )
        endif()
        unset(_sdl2mixer_dll)
        unset(_sdl2mixer_imp)
    else()
        set(_sdl2mixer_shl "${_sdl2mixer_libdir}/${CMAKE_SHARED_LIBRARY_PREFIX}SDL2_mixer${CMAKE_SHARED_LIBRARY_SUFFIX}")
        if(EXISTS "${_sdl2mixer_shl}")
            add_library(SDL2_mixer::SDL2_mixer SHARED IMPORTED)
            set_target_properties(SDL2_mixer::SDL2_mixer
                PROPERTIES
                    IMPORTED_LOCATION "${_sdl2mixer_shl}"
            )
        endif()
    endif()
    if(TARGET SDL2_mixer::SDL2_mixer)
        set_target_properties(SDL2_mixer::SDL2_mixer
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${_sdl2mixer_incdir}"
                COMPATIBLE_INTERFACE_BOOL "SDL2_SHARED"
                INTERFACE_SDL2_SHARED "ON"
        )
    endif()
endif()

if(NOT TARGET SDL2_mixer::SDL2_mixer-static)
    set(_sdl2mixer_stl "${_sdl2mixer_libdir}/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer${CMAKE_STATIC_LIBRARY_SUFFIX}")
    if(EXISTS "${_sdl2mixer_stl}")
        add_library(SDL2_mixer::SDL2_mixer-static STATIC IMPORTED)
        set_target_properties(SDL2_mixer::SDL2_mixer-static
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${_sdl2mixer_incdir}"
                IMPORTED_LOCATION "${_sdl2mixer_stl}"
                INTERFACE_LINK_LIBRARIES "${_sdl2mixer_extra_static_libraries}"
        )
    endif()
    unset(_sdl2mixer_stl)
endif()

unset(_sdl2mixer_extra_static_libraries)
unset(_sdl2mixer_bindir)
unset(_sdl2mixer_libdir)
unset(_sdl2mixer_incdir)
