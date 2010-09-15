#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=
CCC=g++412
CXX=g++412
FC=

# Macros
PLATFORM=FOR_MAYA-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/viewSelect.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=-m32

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/autodesk/maya/lib -lFoundation -lOpenMaya -lOpenMayaUI -lOpenMayaAnim

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-release.mk dist/release/${PLATFORM}/libviewSelector.so

dist/release/${PLATFORM}/libviewSelector.so: ${OBJECTFILES}
	${MKDIR} -p dist/release/${PLATFORM}
	${LINK.cc} -shared -o dist/release/${PLATFORM}/libviewSelector.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/viewSelect.o: viewSelect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -w -DLINUX -D_BOOL -DINCLUDE_IOSTREAM -DDREQUIRE_IOSTREAM -DAW_NEW_IOSTREAMS -I/usr/include -I/usr/autodesk/maya/include -fPIC  -o ${OBJECTDIR}/viewSelect.o viewSelect.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/release
	${RM} dist/release/${PLATFORM}/libviewSelector.so

# Subprojects
.clean-subprojects:
