PROJECT(EYE_Player)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/)

MESSAGE(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

include_directories (googletest/googletest/include)
include_directories (${CMAKE_SOURCE_DIR}/../Lib/ffmpeg_install/include)
include_directories (${CMAKE_SOURCE_DIR}/../Lib/ffmpeg_include/include)
include_directories (${CMAKE_SOURCE_DIR}/../Lib/libxml2_install/include)
include_directories (${CMAKE_SOURCE_DIR}/../Lib/libxml2_install/include/libxml2)
include_directories (${CMAKE_SOURCE_DIR}/../Lib/curl_install/include/)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D EYER_PLATFORM_WINDOWS)

    ADD_SUBDIRECTORY(EyerGL)
    ADD_SUBDIRECTORY(EyerCore)
    ADD_SUBDIRECTORY(EyerPlayerJNI)
    ADD_SUBDIRECTORY(EyerGLContext)
    ADD_SUBDIRECTORY(EyerThread)
    ADD_SUBDIRECTORY(EyerAV)
    ADD_SUBDIRECTORY(EyerGLShader)
    ADD_SUBDIRECTORY(EyerPlayer)
    ADD_SUBDIRECTORY(EyerEventQueue)
    ADD_SUBDIRECTORY(EyerPlayerMain)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    ADD_DEFINITIONS(-D EYER_PLATFORM_ANDROID)

    ADD_SUBDIRECTORY(EyerGL)
    ADD_SUBDIRECTORY(EyerCore)
    ADD_SUBDIRECTORY(EyerPlayerJNI)
    ADD_SUBDIRECTORY(EyerGLContext)
    ADD_SUBDIRECTORY(EyerThread)
    ADD_SUBDIRECTORY(EyerAV)
    ADD_SUBDIRECTORY(EyerGLShader)
    ADD_SUBDIRECTORY(EyerPlayer)
    ADD_SUBDIRECTORY(EyerEventQueue)
    ADD_SUBDIRECTORY(EyerGLRenderTask)
    ADD_SUBDIRECTORY(EyerCodec)
    ADD_SUBDIRECTORY(EyerJNI)
    ADD_SUBDIRECTORY(EyerOpenSL)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


