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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Verbose
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/common/encoding.o \
	${OBJECTDIR}/common/hashing.o \
	${OBJECTDIR}/common/kadmin/kadmin_common.o \
	${OBJECTDIR}/common/kdc/kdc_common.o \
	${OBJECTDIR}/common/user/user_common.o \
	${OBJECTDIR}/common/utils.o \
	${OBJECTDIR}/debug.o \
	${OBJECTDIR}/fnasso.o \
	${OBJECTDIR}/interfaces/ikadmin.o \
	${OBJECTDIR}/interfaces/ikdc.o \
	${OBJECTDIR}/interfaces/iuser.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lkrb5 -lcrypto -lssl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfnasso

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfnasso: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfnasso ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/common/encoding.o: common/encoding.c 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/encoding.o common/encoding.c

${OBJECTDIR}/common/hashing.o: common/hashing.c 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/hashing.o common/hashing.c

${OBJECTDIR}/common/kadmin/kadmin_common.o: common/kadmin/kadmin_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/kadmin
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/kadmin/kadmin_common.o common/kadmin/kadmin_common.c

${OBJECTDIR}/common/kdc/kdc_common.o: common/kdc/kdc_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/kdc
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/kdc/kdc_common.o common/kdc/kdc_common.c

${OBJECTDIR}/common/user/user_common.o: common/user/user_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/user
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/user/user_common.o common/user/user_common.c

${OBJECTDIR}/common/utils.o: common/utils.c 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/utils.o common/utils.c

${OBJECTDIR}/debug.o: debug.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug.o debug.c

${OBJECTDIR}/fnasso.o: fnasso.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fnasso.o fnasso.c

${OBJECTDIR}/interfaces/ikadmin.o: interfaces/ikadmin.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/ikadmin.o interfaces/ikadmin.c

${OBJECTDIR}/interfaces/ikdc.o: interfaces/ikdc.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/ikdc.o interfaces/ikdc.c

${OBJECTDIR}/interfaces/iuser.o: interfaces/iuser.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/iuser.o interfaces/iuser.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/encoding.o ${TESTDIR}/tests/hashing.o ${TESTDIR}/tests/kadmin.o ${TESTDIR}/tests/kdc.o ${TESTDIR}/tests/main.o ${TESTDIR}/tests/user.o ${TESTDIR}/tests/utils.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/encoding.o: tests/encoding.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/encoding.o tests/encoding.c


${TESTDIR}/tests/hashing.o: tests/hashing.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/hashing.o tests/hashing.c


${TESTDIR}/tests/kadmin.o: tests/kadmin.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/kadmin.o tests/kadmin.c


${TESTDIR}/tests/kdc.o: tests/kdc.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/kdc.o tests/kdc.c


${TESTDIR}/tests/main.o: tests/main.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/main.o tests/main.c


${TESTDIR}/tests/user.o: tests/user.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/user.o tests/user.c


${TESTDIR}/tests/utils.o: tests/utils.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DTRACE_MODE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/utils.o tests/utils.c


${OBJECTDIR}/common/encoding_nomain.o: ${OBJECTDIR}/common/encoding.o common/encoding.c 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/encoding.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/encoding_nomain.o common/encoding.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/encoding.o ${OBJECTDIR}/common/encoding_nomain.o;\
	fi

${OBJECTDIR}/common/hashing_nomain.o: ${OBJECTDIR}/common/hashing.o common/hashing.c 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/hashing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/hashing_nomain.o common/hashing.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/hashing.o ${OBJECTDIR}/common/hashing_nomain.o;\
	fi

${OBJECTDIR}/common/kadmin/kadmin_common_nomain.o: ${OBJECTDIR}/common/kadmin/kadmin_common.o common/kadmin/kadmin_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/kadmin
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/kadmin/kadmin_common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/kadmin/kadmin_common_nomain.o common/kadmin/kadmin_common.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/kadmin/kadmin_common.o ${OBJECTDIR}/common/kadmin/kadmin_common_nomain.o;\
	fi

${OBJECTDIR}/common/kdc/kdc_common_nomain.o: ${OBJECTDIR}/common/kdc/kdc_common.o common/kdc/kdc_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/kdc
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/kdc/kdc_common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/kdc/kdc_common_nomain.o common/kdc/kdc_common.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/kdc/kdc_common.o ${OBJECTDIR}/common/kdc/kdc_common_nomain.o;\
	fi

${OBJECTDIR}/common/user/user_common_nomain.o: ${OBJECTDIR}/common/user/user_common.o common/user/user_common.c 
	${MKDIR} -p ${OBJECTDIR}/common/user
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/user/user_common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/user/user_common_nomain.o common/user/user_common.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/user/user_common.o ${OBJECTDIR}/common/user/user_common_nomain.o;\
	fi

${OBJECTDIR}/common/utils_nomain.o: ${OBJECTDIR}/common/utils.o common/utils.c 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/utils_nomain.o common/utils.c;\
	else  \
	    ${CP} ${OBJECTDIR}/common/utils.o ${OBJECTDIR}/common/utils_nomain.o;\
	fi

${OBJECTDIR}/debug_nomain.o: ${OBJECTDIR}/debug.o debug.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/debug.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug_nomain.o debug.c;\
	else  \
	    ${CP} ${OBJECTDIR}/debug.o ${OBJECTDIR}/debug_nomain.o;\
	fi

${OBJECTDIR}/fnasso_nomain.o: ${OBJECTDIR}/fnasso.o fnasso.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/fnasso.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fnasso_nomain.o fnasso.c;\
	else  \
	    ${CP} ${OBJECTDIR}/fnasso.o ${OBJECTDIR}/fnasso_nomain.o;\
	fi

${OBJECTDIR}/interfaces/ikadmin_nomain.o: ${OBJECTDIR}/interfaces/ikadmin.o interfaces/ikadmin.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interfaces/ikadmin.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/ikadmin_nomain.o interfaces/ikadmin.c;\
	else  \
	    ${CP} ${OBJECTDIR}/interfaces/ikadmin.o ${OBJECTDIR}/interfaces/ikadmin_nomain.o;\
	fi

${OBJECTDIR}/interfaces/ikdc_nomain.o: ${OBJECTDIR}/interfaces/ikdc.o interfaces/ikdc.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interfaces/ikdc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/ikdc_nomain.o interfaces/ikdc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/interfaces/ikdc.o ${OBJECTDIR}/interfaces/ikdc_nomain.o;\
	fi

${OBJECTDIR}/interfaces/iuser_nomain.o: ${OBJECTDIR}/interfaces/iuser.o interfaces/iuser.c 
	${MKDIR} -p ${OBJECTDIR}/interfaces
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interfaces/iuser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DTRACE_MODE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interfaces/iuser_nomain.o interfaces/iuser.c;\
	else  \
	    ${CP} ${OBJECTDIR}/interfaces/iuser.o ${OBJECTDIR}/interfaces/iuser_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfnasso

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
