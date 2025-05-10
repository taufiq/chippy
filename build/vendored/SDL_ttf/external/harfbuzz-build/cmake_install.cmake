# Install script for directory: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/harfbuzz" TYPE FILE FILES
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-aat-layout.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-aat.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-blob.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-buffer.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-common.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-cplusplus.hh"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-deprecated.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-draw.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-face.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-font.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-map.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-color.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-deprecated.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-font.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-layout.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-math.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-meta.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-metrics.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-name.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-shape.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-var.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ot.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-paint.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-set.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-shape-plan.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-shape.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-style.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-unicode.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-version.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-ft.h"
    "/Users/taufiq/Documents/chippy/vendored/SDL_ttf/external/harfbuzz/src/hb-coretext.h"
    )
endif()

