# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/taufiq/Documents/chippy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/taufiq/Documents/chippy/build

# Include any dependencies generated for this target.
include vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.make

# Include the progress variables for this target.
include vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/progress.make

# Include the compile flags for this target's objects.
include vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.s

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable_ttf.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable_ttf.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable_ttf.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_hashtable_ttf.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.s

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_gpu_textengine.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_gpu_textengine.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_gpu_textengine.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_gpu_textengine.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.s

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_renderer_textengine.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_renderer_textengine.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_renderer_textengine.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_renderer_textengine.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.s

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_surface_textengine.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_surface_textengine.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_surface_textengine.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_surface_textengine.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.s

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/flags.make
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o: /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_ttf.c
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o -MF CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o.d -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o -c /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_ttf.c

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.i"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_ttf.c > CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.i

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.s"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/taufiq/Documents/chippy/vendored/SDL_ttf/src/SDL_ttf.c -o CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.s

# Object files for target SDL3_ttf-shared
SDL3_ttf__shared_OBJECTS = \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o" \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o" \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o" \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o" \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o" \
"CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o"

# External object files for target SDL3_ttf-shared
SDL3_ttf__shared_EXTERNAL_OBJECTS =

libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_hashtable_ttf.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_gpu_textengine.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_renderer_textengine.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_surface_textengine.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/src/SDL_ttf.c.o
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/build.make
libSDL3_ttf.0.3.0.dylib: SDL3.framework/Versions/A/SDL3
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/external/plutosvg-guild/libplutosvg.a
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/external/harfbuzz-build/libharfbuzz.a
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/external/freetype-build/libfreetype.a
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/external/plutovg-build/libplutovg.a
libSDL3_ttf.0.3.0.dylib: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.0.sdk/usr/lib/libm.tbd
libSDL3_ttf.0.3.0.dylib: /Users/taufiq/Documents/chippy/vendored/SDL/src/dynapi/SDL_dynapi.sym
libSDL3_ttf.0.3.0.dylib: vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/taufiq/Documents/chippy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library ../../libSDL3_ttf.dylib"
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL3_ttf-shared.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && $(CMAKE_COMMAND) -E cmake_symlink_library ../../libSDL3_ttf.0.3.0.dylib ../../libSDL3_ttf.0.dylib ../../libSDL3_ttf.dylib

libSDL3_ttf.0.dylib: libSDL3_ttf.0.3.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libSDL3_ttf.0.dylib

libSDL3_ttf.dylib: libSDL3_ttf.0.3.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libSDL3_ttf.dylib

# Rule to build all files generated by this target.
vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/build: libSDL3_ttf.dylib
.PHONY : vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/build

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/clean:
	cd /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf && $(CMAKE_COMMAND) -P CMakeFiles/SDL3_ttf-shared.dir/cmake_clean.cmake
.PHONY : vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/clean

vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/depend:
	cd /Users/taufiq/Documents/chippy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/taufiq/Documents/chippy /Users/taufiq/Documents/chippy/vendored/SDL_ttf /Users/taufiq/Documents/chippy/build /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf /Users/taufiq/Documents/chippy/build/vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : vendored/SDL_ttf/CMakeFiles/SDL3_ttf-shared.dir/depend

