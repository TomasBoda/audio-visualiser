# Install script for directory: /Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/libraries/wxWidgets

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  message(STATUS "Installing: Headers...")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wx-3.2" TYPE DIRECTORY FILES "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/libraries/wxWidgets/include/wx")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/wx/include" TYPE DIRECTORY FILES "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/lib/wx/include/osx_cocoa-unicode-3.2")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/wx/config" TYPE FILE PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ FILES "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/lib/wx/config/osx_cocoa-unicode-3.2")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE DIRECTORY FILES "")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(         COMMAND /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E create_symlink         "/usr/local/lib/wx/config/osx_cocoa-unicode-3.2"         "$ENV{DESTDIR}/usr/local/bin/wx-config"         )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/wxWidgetsTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/wxWidgetsTargets.cmake"
         "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/CMakeFiles/Export/lib/cmake/wxWidgets/wxWidgetsTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/wxWidgetsTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/wxWidgetsTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets" TYPE FILE FILES "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/CMakeFiles/Export/lib/cmake/wxWidgets/wxWidgetsTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets" TYPE FILE FILES "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/CMakeFiles/Export/lib/cmake/wxWidgets/wxWidgetsTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets" TYPE FILE FILES
    "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/lib/wxWidgetsConfig.cmake"
    "/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/lib/wxWidgetsConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/libs/cmake_install.cmake")
  include("/Users/tomasboda/Documents/Workspace/C++/exam/fft-music-visualiser/cmake-build-debug/libraries/wxWidgets/utils/cmake_install.cmake")

endif()

