cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(tomatenquark CXX)

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
        add_definitions(-DWIN64)
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

############### Dependencies ##########

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

find_package(ZLIB REQUIRED)
find_package(ENet REQUIRED)

include(FetchContent)
FetchContent_Declare(
        backwards-cpp
        GIT_REPOSITORY    https://github.com/bombela/backward-cpp.git
        GIT_TAG           v1.5
)
FetchContent_MakeAvailable(backwards-cpp)

list(APPEND GOTQ_LINKING_LIBRARIES_BASE "ZLIB::ZLIB" "${ENET_LIBRARY}")

find_package(SDL2 CONFIG)
find_package(sdl2-image CONFIG)
find_package(sdl2-mixer CONFIG)
find_package(Steam)

if(SDL2_FOUND)
    list(APPEND GOTQ_LINKING_LIBRARIES_CLIENT "SDL2::SDL2-static")
endif()

if(sdl2-image_FOUND)
    list(APPEND GOTQ_LINKING_LIBRARIES_CLIENT "SDL2::SDL2_image")
endif()

if(sdl2-mixer_FOUND)
    list(APPEND GOTQ_LINKING_LIBRARIES_CLIENT "SDL2::SDL2_mixer")
endif()

if(STEAM_FOUND)
    list(APPEND GOTQ_LINKING_LIBRARIES_BASE "${STEAM_LIBRARY}")
endif()

################ Files ################

include_directories(src/shared src/engine src/fpsgame src/integration)

if(WIN32)
    set(GOTQ_APPLICATION_CLIENT_TYPE "WIN32")
    set(GOTQ_ADDITIONAL_SOURCE_FILES "cmake/vcpp/tomatenquarkrc.rc")
elseif(APPLE)
    enable_language(OBJC)
    set(GOTQ_APPLICATION_CLIENT_TYPE "MACOSX_BUNDLE")
    set(GOTQ_ADDITIONAL_SOURCE_FILES "cmake/xcode/main.m" "cmake/xcode/Launcher.m")
else()
    set(GOTQ_APPLICATION_CLIENT_TYPE "")
    set(GOTQ_ADDITIONAL_SOURCE_FILES "")
endif()

if(STEAM_FOUND)
    include_directories("${STEAM_INCLUDE_DIR}")
    set(GOTQ_ADDITIONAL_SOURCE_FILES "${GOTQ_ADDITIONAL_SOURCE_FILES}")
endif()

add_executable(tomaten_master
        src/shared/crypto.cpp
        src/shared/stream.cpp
        src/shared/tools.cpp
        src/engine/command.cpp
        src/engine/master.cpp
        ${BACKWARD_ENABLE}
)

target_compile_definitions(tomaten_master PUBLIC STANDALONE)

add_executable(tomaten_server
        src/shared/crypto.cpp
        src/shared/stream.cpp
        src/shared/tools.cpp
        src/engine/command.cpp
        src/engine/server.cpp
        src/engine/worldio.cpp
        src/fpsgame/entities.cpp
        src/fpsgame/server.cpp
        ${BACKWARD_ENABLE}
)

target_compile_definitions(tomaten_server PUBLIC STANDALONE)
if(STEAM_FOUND)
    target_compile_definitions(tomaten_server PUBLIC STEAM_ENABLED)
endif()

if(WIN32)
   set_target_properties(tomaten_master tomaten_server PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
endif()

add_executable(${CMAKE_PROJECT_NAME} ${GOTQ_APPLICATION_CLIENT_TYPE}
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
        ${GOTQ_ADDITIONAL_SOURCE_FILES}
        ${BACKWARD_ENABLE}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CLIENT)

if(STEAM_FOUND)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC STEAM_ENABLED)
endif()

if(APPLE)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/cmake/xcode/tomatenquark.plist"
    )
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/xcode/Resources
        $<TARGET_BUNDLE_CONTENT_DIR:${CMAKE_PROJECT_NAME}>/Resources
    )
endif()

############## Linking ###

if(WIN32)
    list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_CLIENT "opengl32" "ws2_32" "dbghelp" "winmm" "kernel32" "user32")
    list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_SERVER "ws2_32" "winmm")
    list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_MASTER "ws2_32" "winmm")
elseif(APPLE)
    list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_CLIENT "-framework AudioUnit" "-framework OpenGL")
else()
    list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_CLIENT "GL" "rt")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_CLIENT "stdc++fs")
        list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_SERVER "stdc++fs")
        list(APPEND GOTQ_LINKING_PLATFORM_SPECIFIC_MASTER "stdc++fs")
    endif()
    # Server doesn't need more libs linked on UNIX
endif()


target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${GOTQ_LINKING_LIBRARIES_BASE} ${GOTQ_LINKING_LIBRARIES_CLIENT} ${GOTQ_LINKING_PLATFORM_SPECIFIC_CLIENT})
target_link_libraries(tomaten_server PRIVATE ${GOTQ_LINKING_LIBRARIES_BASE} ${GOTQ_LINKING_PLATFORM_SPECIFIC_SERVER})
target_link_libraries(tomaten_master PRIVATE ${GOTQ_LINKING_LIBRARIES_BASE} ${GOTQ_LINKING_PLATFORM_SPECIFIC_MASTER})

################ Install targets ################
set(GOTQ_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin_unix")

if(WIN32)
    if(BUILD_TARGET_X86)
        set(GOTQ_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin")
    else()
        set(GOTQ_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin64")
    endif()
elseif(UNIX AND NOT APPLE)
    set(GOTQ_TARGET_DIR "${PROJECT_SOURCE_DIR}/bin_unix")
    if(BUILD_TARGET_X86)
        set(GOTQ_TARGET_UNIX_EXECUTABLE "linux_32_client")
    else()
        set(GOTQ_TARGET_UNIX_EXECUTABLE "linux_64_client")
    endif()
endif()

if(WIN32)
    install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${GOTQ_TARGET_DIR})
elseif(UNIX AND NOT APPLE)
    install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${GOTQ_TARGET_DIR} RENAME ${GOTQ_TARGET_UNIX_EXECUTABLE})
endif()
