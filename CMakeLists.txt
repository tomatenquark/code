cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(sauerbraten CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif()


################# Flags ################

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /GL /Od /Zi")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /GL /Od /Zi")
   SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /LTCG")
endif()

if(NOT MSVC)
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()

   set(BUILD_C_FLAGS "${BUILD_C_FLAGS} -fomit-frame-pointer -Wall -fsigned-char")
   set(BUILD_CXX_FLAGS "${BUILD_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BUILD_TARGET_X64 1)
else()
    set(BUILD_TARGET_X86 1)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FLAGS "${BUILD_FLAGS} -DWINDOWS")
    if(BUILD_TARGET_X64)
        set(BUILD_FLAGS "${BUILD_FLAGS} -DWIN64")
    else()
        set(BUILD_FLAGS "${BUILD_FLAGS} -DWIN32")
    endif()
endif()

set(BUILD_DEBUG_FLAGS   "${BUILD_FLAGS} -D_DEBUG -DBUILD_DEBUG -DCLIENT")
set(BUILD_RELEASE_FLAGS "${BUILD_FLAGS} -DNDEBUG -DBUILD_NO_DEBUG")

set(BUILD_C_DEBUG_FLAGS "${BUILD_C_FLAGS} ${BUILD_DEBUG_FLAGS}")
set(BUILD_CXX_DEBUG_FLAGS "${BUILD_CXX_FLAGS} ${BUILD_DEBUG_FLAGS}")

set(BUILD_C_RELEASE_FLAGS "${BUILD_C_FLAGS} ${BUILD_RELEASE_FLAGS}")
set(BUILD_CXX_RELEASE_FLAGS "${BUILD_CXX_FLAGS} ${BUILD_RELEASE_FLAGS}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${BUILD_C_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${BUILD_CXX_DEBUG_FLAGS}")
message(STATUS "Set debug mode flags (${BUILD_DEBUG_FLAGS}) (Current mode: ${CMAKE_BUILD_TYPE}, compiler: ${CMAKE_CXX_COMPILER_ID})")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${BUILD_C_RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${BUILD_CXX_RELEASE_FLAGS}")
message(STATUS "Set release mode flags (${BUILD_RELEASE_FLAGS}) (Current mode: ${CMAKE_BUILD_TYPE}, compiler: ${CMAKE_CXX_COMPILER_ID})")



# --- Conan --- #
# Download Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake v0.15 from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/b9fdb9f674e89d990c7764117cd26ae2693ff022/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

# Include Conan CMake wrapper
cmake_policy(SET CMP0025 NEW)

include(${CMAKE_BINARY_DIR}/conan.cmake)

# Make sure we have a recent Conan version
conan_check(VERSION 1.21.0 REQUIRED)

# Install Bincrafters Conan repository if not already installed
conan_add_remote(NAME bincrafters INDEX 1
        URL https://api.bintray.com/conan/bincrafters/public-conan)

# Execute `conan install ...` for the packages in conanfile.txt
conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP # CMAKE_TARGETS
        BUILD outdated
        UPDATE
        )


################ Files ################

include_directories(src/shared src/engine src/fpsgame)

if(WIN32)
    set(GOSAUR_APPLICATION_TYPE "WIN32")
    set(GOSAUR_ADDITIONAL_SOURCE_FILES "src/vcpp/sauerbraten.rc")
else()
    set(GOSAUR_APPLICATION_TYPE "")
    set(GOSAUR_ADDITIONAL_SOURCE_FILES "")
endif()


add_executable(sauer_master
        src/shared/crypto.cpp
        src/shared/stream.cpp
        src/shared/tools.cpp
        src/engine/command.cpp
        src/engine/master.cpp
        ${GOSAUR_ADDITIONAL_SOURCE_FILES}
)

target_compile_definitions(sauer_master PUBLIC STANDALONE)


add_executable(sauer_server ${GOSAUR_APPLICATION_TYPE}
        src/shared/crypto.cpp
        src/shared/stream.cpp
        src/shared/tools.cpp
        src/engine/command.cpp
        src/engine/server.cpp
        src/engine/worldio.cpp
        src/fpsgame/entities.cpp
        src/fpsgame/server.cpp
        ${GOSAUR_ADDITIONAL_SOURCE_FILES}
)

target_compile_definitions(sauer_server PUBLIC STANDALONE)


add_executable(${CMAKE_PROJECT_NAME} ${GOSAUR_APPLICATION_TYPE}
        src/shared/crypto.cpp
        src/shared/cube2font.c
        src/shared/geom.cpp
        src/shared/glemu.cpp
        src/shared/pch.cpp
        src/shared/stream.cpp
        src/shared/tools.cpp
        src/shared/zip.cpp
        src/engine/3dgui.cpp
        src/engine/bih.cpp
        src/engine/blend.cpp
        src/engine/blob.cpp
        src/engine/client.cpp
        src/engine/command.cpp
        src/engine/console.cpp
        src/engine/cubeloader.cpp
        src/engine/decal.cpp
        src/engine/dynlight.cpp
        src/engine/glare.cpp
        src/engine/grass.cpp
        src/engine/lightmap.cpp
        src/engine/main.cpp
        src/engine/material.cpp
        src/engine/menus.cpp
        src/engine/movie.cpp
        src/engine/normal.cpp
        src/engine/octa.cpp
        src/engine/octaedit.cpp
        src/engine/octarender.cpp
        src/engine/pch.cpp
        src/engine/physics.cpp
        src/engine/pvs.cpp
        src/engine/rendergl.cpp
        src/engine/rendermodel.cpp
        src/engine/renderparticles.cpp
        src/engine/rendersky.cpp
        src/engine/rendertext.cpp
        src/engine/renderva.cpp
        src/engine/server.cpp
        src/engine/serverbrowser.cpp
        src/engine/shader.cpp
        src/engine/shadowmap.cpp
        src/engine/sound.cpp
        src/engine/texture.cpp
        src/engine/water.cpp
        src/engine/world.cpp
        src/engine/worldio.cpp
        src/fpsgame/ai.cpp
        src/fpsgame/client.cpp
        src/fpsgame/entities.cpp
        src/fpsgame/fps.cpp
        src/fpsgame/monster.cpp
        src/fpsgame/movable.cpp
        src/fpsgame/pch.cpp
        src/fpsgame/render.cpp
        src/fpsgame/scoreboard.cpp
        src/fpsgame/server.cpp
        src/fpsgame/waypoint.cpp
        src/fpsgame/weapon.cpp
        ${GOSAUR_ADDITIONAL_SOURCE_FILES}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CLIENT)

# enet.lib;zdll.lib;opengl32.lib;SDL2.lib;SDL2_image.lib;ws2_32.lib;SDL2_mixer.lib;winmm.lib;dbghelp.lib;kernel32.lib;user32.lib


if(WIN32)
    list(APPEND GOSAUR_LINKING_PLATFORM_SPECIFIC_CLIENT "opengl32" "ws2_32" "dbghelp" "winmm" "kernel32" "user32")
    list(APPEND GOSAUR_LINKING_PLATFORM_SPECIFIC_SERVER "ws2_32" "winmm")
    list(APPEND GOSAUR_LINKING_PLATFORM_SPECIFIC_MASTER "ws2_32" "winmm")
else()
    list(APPEND GOSAUR_LINKING_PLATFORM_SPECIFIC_CLIENT "GL")
    # Server doesn't need more libs linked on UNIX
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS} ${GOSAUR_LINKING_PLATFORM_SPECIFIC_CLIENT})
target_link_libraries(sauer_server ${CONAN_LIBS} ${GOSAUR_LINKING_PLATFORM_SPECIFIC_SERVER})
target_link_libraries(sauer_master ${CONAN_LIBS} ${GOSAUR_LINKING_PLATFORM_SPECIFIC_MASTER})
# target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS} opengl32 ws2_32 dbghelp winmm kernel32 user32)
# target_link_libraries(${CMAKE_PROJECT_NAME} ENET::ENET SDL2_IMAGE::SDL2_image SDL2_MIXER::SDL2_MIXER ZLIB::ZLIB SDL2::SDL2 opengl32)

    
message(STATUS "CONAN_LIBS='${CONAN_LIBS}'")


################ Install targets ################
set(GOSAUR_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin_unix")

if(WIN32)
    if(BUILD_TARGET_X86)
        set(GOSAUR_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin")
    else()
        set(GOSAUR_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin64")
    endif()
endif()

install(TARGETS ${CMAKE_PROJECT_NAME} sauer_server sauer_master RUNTIME DESTINATION ${GOSAUR_TARGET_DIR})

