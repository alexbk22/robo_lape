# Install script for directory: /home/pi/git/robo_lape/src/actionlib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/git/robo_lape/install")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/pi/git/robo_lape/build/actionlib/catkin_generated/safe_execute_install.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/action" TYPE FILE FILES
    "/home/pi/git/robo_lape/src/actionlib/action/Test.action"
    "/home/pi/git/robo_lape/src/actionlib/action/TestRequest.action"
    "/home/pi/git/robo_lape/src/actionlib/action/TwoInts.action"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/msg" TYPE FILE FILES
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestAction.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestActionGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestActionResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestActionFeedback.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestFeedback.msg"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/msg" TYPE FILE FILES
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestAction.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestActionGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestActionResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestActionFeedback.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TestRequestFeedback.msg"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/msg" TYPE FILE FILES
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsAction.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsActionGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsActionResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsActionFeedback.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsGoal.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsResult.msg"
    "/home/pi/git/robo_lape/devel/share/actionlib/msg/TwoIntsFeedback.msg"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/cmake" TYPE FILE FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/actionlib-msg-paths.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/include/actionlib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/share/roseus/ros/actionlib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/share/common-lisp/ros/actionlib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/share/gennodejs/ros/actionlib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/pi/git/robo_lape/devel/lib/python2.7/dist-packages/actionlib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/lib/python2.7/dist-packages/actionlib" REGEX "/\\_\\_init\\_\\_\\.py$" EXCLUDE REGEX "/\\_\\_init\\_\\_\\.pyc$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/devel/lib/python2.7/dist-packages/actionlib" FILES_MATCHING REGEX "/home/pi/git/robo_lape/devel/lib/python2.7/dist-packages/actionlib/.+/__init__.pyc?$")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/actionlib.pc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/cmake" TYPE FILE FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/actionlib-msg-extras.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib/cmake" TYPE FILE FILES
    "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/actionlibConfig.cmake"
    "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/actionlibConfig-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/actionlib" TYPE FILE FILES "/home/pi/git/robo_lape/src/actionlib/package.xml")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/actionlib" TYPE PROGRAM FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/axclient.py")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/actionlib" TYPE PROGRAM FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/axserver.py")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/actionlib" TYPE PROGRAM FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/dynamic_action.py")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/actionlib" TYPE PROGRAM FILES "/home/pi/git/robo_lape/build/actionlib/catkin_generated/installspace/library.py")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pi/git/robo_lape/devel/lib/libactionlib.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so"
         OLD_RPATH "/opt/ros/kinetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libactionlib.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/actionlib" TYPE DIRECTORY FILES "/home/pi/git/robo_lape/src/actionlib/include/actionlib/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pi/git/robo_lape/build/actionlib/test/cmake_install.cmake")

endif()

