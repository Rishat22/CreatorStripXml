# Top level project
project(CreatorStripXml)

set(PROJECT_NAME CreatorStripXml)

# Minimum required version of CMake
cmake_minimum_required(VERSION 2.6)

# CMake modules path
set(CMAKE_MODULE_PATH ${SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH})

# Support for precompiled headers
include(UProjectSupport.cmake)

# Package search
include(FindPkgConfig)


# Test for C++ support
enable_language(CXX)

# Get build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

# set up debug postfix
set(CMAKE_DEBUG_POSTFIX d)

# Type of build
if(UNIX)
	if(BUILD_TYPE STREQUAL "DEBUG")
		# set QT_DEBUG definition (workaround for PCH support)
		add_definitions(-DQT_DEBUG -DQT_DLL)
		set(DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	else(BUILD_TYPE STREQUAL "DEBUG")
		# set QT_NODEBUG definition (workaround for PCH support)
		add_definitions(-DQT_NO_DEBUG -DQT_DLL)
	endif(BUILD_TYPE STREQUAL "DEBUG")
endif(UNIX)

# Setup global include path
set(INCLUDE_PATH "${SOURCE_DIR}")
include_directories(${INCLUDE_PATH})


# FFMPEG - resides in binary directory
include_directories(${CMAKE_BINARY_DIR}/include)

# Project type (all, servers, ...)
if(NOT PROJ_TYPE)
	set(PROJ_TYPE all)
endif()

string(TOUPPER ${PROJ_TYPE} PROJ_TYPE)

if(${PROJ_TYPE} MATCHES "ALL")

	# Test for Qt support
	set(QT_REQUIRED TRUE)

	if(NOT ULIB_USE_QT4 AND NOT ULIB_USE_QT5)
		option(ULIB_USE_QT4 "Build Galaxy with Qt4 support." off)
		option(ULIB_USE_QT5 "Build Galaxy with Qt5 support by default." on)
	endif()

	if(ULIB_USE_QT4)
		# Qt4 option
		find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtNetwork QtWebKit REQUIRED)
		if(Qt4_FOUND)
			set(ULIB_QT_VERSION ${Qt4_VERSION})
			message("Build Galaxy with Qt ${ULIB_QT_VERSION}")
		else()
			message(SEND_ERROR "Qt4 not found.")
		endif()
	elseif(ULIB_USE_QT5)
		# Qt5 option
		find_package(Qt5 COMPONENTS Core Gui Widgets)
		if(Qt5_FOUND)
			set(ULIB_QT_VERSION ${Qt5_VERSION})
			message("Build Galaxy with Qt ${ULIB_QT_VERSION}")
		else()
			message(SEND_ERROR "Qt5 not found.")
		endif()
	endif()

	# Audio player
	option(WITH_AUDIOPLAYER "Build CWP with audio player." off)
	if(WITH_AUDIOPLAYER)
		add_definitions(-DWITH_AUDIOPLAYER)
		message("AUDIOPLAYER ON")
	endif(WITH_AUDIOPLAYER)

	# CG Window
	option(WITH_CGWINDOW "Build CWP with CG Window." off)
	if(WITH_CGWINDOW)
		add_definitions(-DWITH_CGWINDOW)
		message("CGWINDOW ON")
	endif(WITH_CGWINDOW)

	# AIXM
	option(WITH_AIXM "Build CWP with AIXM Converter." off)
	if(WITH_AIXM)
		add_definitions(-DWITH_AIXM)
		message("AIXM ON")
	endif(WITH_AIXM)

	# VCS
	option(WITH_VCS "Build with VCS." off)
	if(WITH_VCS)
		add_definitions(-DWITH_VCS)
		message("VCS ON")
	endif(WITH_VCS)

	# GPT
	option(WITH_GPT "Build with GPT." off)
	if(WITH_GPT)
		add_definitions(-DWITH_GPT)
		message("GPT ON")
	endif(WITH_GPT)

	# SmartCard
	option(WITH_SCSUPPORT "Build with SmartCard support." off)
	if(WITH_SCSUPPORT)
		add_definitions(-DWITH_SCSUPPORT)
		message("SCSUPPORT ON")

		find_package(PCSC REQUIRED)

		if(PCSC_FOUND)
			#Add include directory
			include_directories(${PCSC_INCLUDE_DIRS})
		else()
			message(FATAL_ERROR "pcsclite not found")
		endif(PCSC_FOUND)

	endif(WITH_SCSUPPORT)


	# UNIGINE
	option(WITH_UNIGINE "Build with UNIGINE." off)
	if(WITH_UNIGINE)
		add_definitions(-DWITH_UNIGINE)
		message("UNIGINE ON")
		# Setup unigine path
		set(UNIGINE_INCLUDE_PATH "/usr/local/unigine/")
		message("UNIGINE PATH = ${UNIGINE_INCLUDE_PATH}")
		set(UNIGINE_INCLUDE_PATH "${UNIGINE_INCLUDE_PATH}")
		include_directories(${UNIGINE_INCLUDE_PATH}/include)
		link_directories(${UNIGINE_INCLUDE_PATH}/bin)
	endif(WITH_UNIGINE)

	# VIS_Comtrol Window
	option(WITH_VIS_CONTROL "Build CWP with VIS_Control." off)
	if(WITH_VIS_CONTROL)
		add_definitions(-DWITH_VIS_CONTROL)
		message("VIS_CONTROL ON")
	endif(WITH_VIS_CONTROL)

	# OpenSceneGraph - set custom path
	set(OSG_PATH "${OSG_PATH}")
	include_directories(${OSG_PATH}/include)
	link_directories(${OSG_PATH}/lib)
	link_directories(${OSG_PATH}/lib64)

	# Check OpenSceneGraph version"
	if(OSG_PATH)
		message("OSG_PATH: " ${OSG_PATH})
		execute_process(COMMAND ${OSG_PATH}/bin/osgversion --version-number OUTPUT_VARIABLE OSG_VERSION)
	else(OSG_PATH)
		message("OSG_PATH: " ${OSG_PATH})
		execute_process(COMMAND osgversion --version-number OUTPUT_VARIABLE OSG_VERSION)
	endif(OSG_PATH)

	if(OSG_VERSION)
		message("OSG_VERSION: " ${OSG_VERSION})
	endif(OSG_VERSION)

	# Osg libraries definition
	option(OSG_DEBUG "Build with OpenSceneGraph debug libraries." off)

	# Platform specific options
	if(${U_SYSTEM} MATCHES "DARWIN")
		set(OSG_LIBRARIES
			osg
			osgAnimation
			osgFX
			osgManipulator
			osgParticle
			osgShadow
			osgSim
			osgVolume
			osgWidget
			osgDB
			osgGA
			osgText
			osgUtil
			osgViewer
			osgQt
			osgPresentation
		)
	else()
		if(OSG_DEBUG)
			set(OSG_LIBRARIES
				osgd
				osgDBd
				osgGAd
				osgTextd
				osgUtild
				osgViewerd
			)
		else()
			set(OSG_LIBRARIES
				osg
				osgDB
				osgGA
				osgText
				osgUtil
				osgViewer
			)
		endif()
	endif()
endif()

# Define system: (Windows, Linux, Sun)
string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)
message("Generating makefiles for " ${U_SYSTEM})

# Platform specific options
if(${U_SYSTEM} MATCHES "WINDOWS")
	# set platform
	set(U_PLATFORM WIN)
	# define U_XXX_PLATFORM
	add_definitions(-DU_PLATFORM_WIN)
	# disable warnings on STD non conformance and security issues
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS)
elseif(${U_SYSTEM} MATCHES "LINUX")
	# set platform
	set(U_PLATFORM LINUX)
	# define U_XXX_PLATFORM
	add_definitions(-DU_PLATFORM_LINUX)
	# Enable tr1 functionality
	# add_definitions(-std=c++0x)
	# Enable c++11 standart
	add_definitions(-std=c++11)
	# Enable all warnings
	#add_definitions(-g -Wall)
	add_definitions(-Wall -fno-stack-protector)
	add_definitions(-D__STDC_CONSTANT_MACROS)
	add_definitions(-fPIC)
	# These definitions need to gcc version 4.7.3 (Ubuntu/Linaro 4.7.3-1ubuntu1)
	execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
		add_definitions(-Wno-unused-but-set-variable -Wno-narrowing -Wunused-result)
	endif(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
	# Enable SSE2 intrinsics generation
	add_definitions(-msse2)
elseif(${U_SYSTEM} MATCHES "DARWIN")
	# set platform
	set(U_PLATFORM APPLE)
	# define U_XXX_PLATFORM
	add_definitions(-DU_PLATFORM_APPLE)
	# Enable tr1 functionality
	add_definitions(-stdlib=libc++ -Wno-string-plus-int)
	# Enable SSE2 intrinsics generation
	add_definitions(-msse2)
elseif(${U_SYSTEM} MATCHES "SUNOS")
	# set platform
	set(U_PLATFORM SUNOS)
	# define U_XXX_PLATFORM
	add_definitions(-DU_PLATFORM_SUNOS)
	# Enable SSE2 intrinsics generation
	add_definitions(-msse2)
endif(${U_SYSTEM} MATCHES "WINDOWS")

# Build shared libs option
option(ULIB_BUILD_SHARED_LIBS "Build libraries as shared objects (or dlls)." on)
if(ULIB_BUILD_SHARED_LIBS)
	set(BUILD_SHARED_LIBS true)
endif(ULIB_BUILD_SHARED_LIBS)

# Set library and executable output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Set up search path for libraries
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
if(CMAKE_LIBRARY_PATH)
	set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}:${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
else(CMAKE_LIBRARY_PATH)
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif(CMAKE_LIBRARY_PATH)
# FFMPEG - resides in binary directory
include_directories(${CMAKE_BINARY_DIR}/include)

# Add headers to the project
set(${PROJECT_NAME}_HEADERS
    CMainWidget.h
    CGraphicsItem.h
    CStripLoader.h
    CWdgScene.h
    CWdgSelectionMenu.h
    GlobalSettings.h
    Galaxy/CItemInfoGetter.h
    StableDeclaration.h
)
# Add sources to the project
set(${PROJECT_NAME}_SOURCES
    main.cpp
    CMainWidget.cpp
    CGraphicsItem.cpp
    CStripLoader.cpp
    CWdgScene.cpp
    CWdgSelectionMenu.cpp
    GlobalSettings.cpp
    Galaxy/CItemInfoGetter.cpp
)
# Add library dependencies
set(${PROJECT_NAME}_LIBS
    UTools
    USerialization
    UUserPolicies
)

# subprojects
if(${PROJ_TYPE} MATCHES "SERVERS")
	set(SUBPROJECTS
		${${PROJECT_NAME}_LIBS}
	)
endif()

if(${PROJ_TYPE} MATCHES "ALL")
	set(SUBPROJECTS
		${${PROJECT_NAME}_LIBS}
	)
	if(WITH_AUDIOPLAYER)
		set(SUBPROJECTS ${SUBPROJECTS} UVisualAudioPBC)
	endif()

	if(WITH_VCS)
		set(SUBPROJECTS ${SUBPROJECTS} UVCS VCS)
	endif()

	if(WITH_UNIGINE)
		add_definitions(-std=c++11)
		set(SUBPROJECTS ${SUBPROJECTS} UTwrSimLogic TwrSim)
	endif()
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
# Library subprojects

include_directories(./)

foreach(SUBPROJECT ${SUBPROJECTS})
	# Add subproject
	include_directories(${SUBPROJECT} )
	link_directories(${SUBPROJECT})
	add_subdirectory(${SUBPROJECT})
endforeach(SUBPROJECT)

# Add library and tests for project
uadd_qt_executable(${PROJECT_NAME})
