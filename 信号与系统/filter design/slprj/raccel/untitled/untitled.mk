# Copyright 1994-2018 The MathWorks, Inc.
#
# File    : raccel_lcc64.tmf   
#
# Abstract:
#       Template makefile for building a PC-based "rapid acceleration" 
#       executable from the generated C code for a Simulink model using 
#       generated C code and the
#			LCC compiler Version 2.4
#
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make (gmake) which is located in matlabroot/bin/win32.
#
# 	Note that this template is automatically customized by the build 
#       procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#	build:
#	  OPT_OPTS       - Optimization options. Default is none. To enable
#                          debugging specify as OPT_OPTS=-g4.
#	  OPTS           - User specific compile options.
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#			   (For Lcc, have a '/'as file separator before the
#			   file name instead of a '\' .
#			   i.e.,  d:\work\proj1/myfile.c - required for 'gmake')
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see raccel.tlc

#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the build procedure (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = "%MATLAB%\bin\win64\gmake"
SHELL           = cmd
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = raccel.tlc
BUILD_SUCCESS	= *** Created

# Opt in to simplified format by specifying compatible Toolchain
TOOLCHAIN_NAME = "LCC-win64 v2.4.1 | gmake (64-bit Windows)"

MAKEFILE_FILESEP = /

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# build procedure.
#
#  MODEL_NAME          - Name of the Simulink block diagram
#  MODEL_MODULES       - Any additional generated source modules
#  MAKEFILE_NAME       - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT         - Path to where MATLAB is installed.
#  MATLAB_BIN          - Path to MATLAB executable.
#  S_FUNCTIONS_LIB     - List of S-functions libraries to link.
#  BUILDARGS           - Options passed in at the command line.

MODEL               = untitled
MODULES             = rt_logging.c rtGetInf.c rtGetNaN.c rt_nonfinite.c untitled.c untitled_capi.c untitled_data.c untitled_tgtconn.c rt_logging_mmi.c rtw_modelmap_utils.c raccel_main_new.c raccel_sup.c raccel_mat.c simulink_solver_api.c raccel_utils.c common_utils.c ext_svr.c updown.c ext_work.c rtiostream_interface.c rtiostream_tcpip.c rtiostream_utils.c
MAKEFILE            = untitled.mk
MATLAB_ROOT         = D:/MATLAB/R2019a
ALT_MATLAB_ROOT     = D:/MATLAB/R2019a
MATLAB_BIN          = D:/MATLAB/R2019a/bin
ALT_MATLAB_BIN      = D:/MATLAB/R2019a/bin
MASTER_ANCHOR_DIR   = 
START_DIR           = D:/_UNIVE~1/_current/MATLAB/FILTER~1
S_FUNCTIONS_LIB     = $(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwcoder_target_services.lib $(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwcoder_ParamTuningTgtAppSvc.lib $(MATLAB_ROOT)\sys\lcc64\lcc64\lib64\wsock32.lib
BUILDARGS           =  MODELLIB=untitledlib.lib RSIM_SOLVER_SELECTION=2 EXTMODE_STATIC_ALLOC=0 EXTMODE_STATIC_ALLOC_SIZE=1000000 EXTMODE_TRANSPORT=0 TMW_EXTMODE_TESTING=0 COMBINE_OUTPUT_UPDATE_FCNS=0 INCLUDE_MDL_TERMINATE_FCN=1 MULTI_INSTANCE_CODE=0 MODELREF_TARGET_TYPE=NONE ISPROTECTINGMODEL=NOTPROTECTING OPTS="-DTGTCONN -DON_TARGET_WAIT_FOR_START=0"

SOLVER              = 

PCMATLABROOT        = D:\\MATLAB\\R2019a

RSIM_PARAMETER_LOADING = 1
ENABLE_SLEXEC_SSBRIDGE = 1
MODELREFS               = 
OPTIMIZATION_FLAGS      = 
ADDITIONAL_LDFLAGS      = 
DEFINES_CUSTOM          = -DEXT_MODE 
SYSTEM_LIBS             = -L"D:\MATLAB\R2019a\extern\lib\win64\microsoft" libmwipp.lib libut.lib libmx.lib libmex.lib libmat.lib libmwmathutil.lib libmwslexec_simbridge.lib libmwsl_fileio.lib libmwsigstream.lib libmwsl_AsyncioQueue.lib libmwsl_simtarget_instrumentation.lib libmwsl_services.lib libmwsdi_raccel.lib libmwsl_log_load_blocks.lib libfixedpoint.lib libmwslexec_simlog.lib

MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0

#--------------------------- Model and reference models -----------------------
MODELREF_LINK_LIBS        = 
MODELREF_LINK_RSPFILE     = untitled_ref.rsp
RELATIVE_PATH_TO_ANCHOR   = ../../..

GLOBAL_TIMING_ENGINE       = 0

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif
ifneq ($(MATLAB_BIN),$(ALT_MATLAB_BIN))
MATLAB_BIN := $(ALT_MATLAB_BIN)
endif
MATLAB_ARCH_BIN = $(MATLAB_BIN)\win64

#---------------------------- Solver ------------------------------------------
RSIM_WITH_SL_SOLVER = 1

#--------------------------- Tool Specifications -------------------------------

LCC = $(MATLAB_ROOT)\sys\lcc64\lcc64
include $(MATLAB_ROOT)\rtw\c\tools\lcc64tools.mak

CMD_FILE             = $(MODEL).rsp

#------------------------------Parameter Tuning---------------------------------
  PARAM_CC_OPTS = -DRSIM_PARAMETER_LOADING

#------------------------------ Include Path -----------------------------------

ADD_INCLUDES = \
	-I$(START_DIR) \
	-I$(START_DIR)/slprj/raccel/untitled \
	-I$(MATLAB_ROOT)/extern/include \
	-I$(MATLAB_ROOT)/simulink/include \
	-I$(MATLAB_ROOT)/rtw/c/src \
	-I$(MATLAB_ROOT)/rtw/c/src/rapid \
	-I$(MATLAB_ROOT)/rtw/c/raccel \
	-I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common \
	-I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src \
	-I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/rtiostreamtcpip \
	-I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils \


# see COMPILER_INCLUDES from lcc64tools.mak

INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(ADD_INCLUDES) \
           $(COMPILER_INCLUDES) $(USER_INCLUDES)

INCLUDES += -I$(MATLAB_ROOT)\rtw\c\raccel -I$(MATLAB_ROOT)\rtw\c\src\rapid

#-------------------------------- C Flags --------------------------------------

# Optimization Options
ifndef OPT_OPTS
OPT_OPTS = $(DEFAULT_OPT_OPTS)
endif

# General User Options
OPTS =

# Compiler options, etc:
ifneq ($(OPTIMIZATION_FLAGS),)
CC_OPTS = $(OPTS) $(ANSI_OPTS)  $(PARAM_CC_OPTS) $(OPTIMIZATION_FLAGS)
else
CC_OPTS = $(OPT_OPTS) $(OPTS) $(ANSI_OPTS)  $(PARAM_CC_OPTS)
endif

CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DHAVESTDIO

CPP_REQ_DEFINES += -DNRT -DRSIM_WITH_SL_SOLVER

ifneq ($(ENABLE_SLEXEC_SSBRIDGE), 0)
   CPP_REQ_DEFINES += -DENABLE_SLEXEC_SSBRIDGE
endif

ifneq ($(MODEL_HAS_DYNAMICALLY_LOADED_SFCNS), 0)
   CPP_REQ_DEFINES += -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS
endif

CFLAGS = $(DEFAULT_CFLAGS) $(CC_OPTS) $(DEFINES_CUSTOM) $(CPP_REQ_DEFINES) $(INCLUDES) -noregistrylookup -w
#----------------------------- Source Files ------------------------------------

PRODUCT            = $(MODEL).exe
BIN_SETTING        = $(LD) $(LDFLAGS) $(ADDITIONAL_LDFLAGS) -o $(PRODUCT) $(SYSLIBS)
BUILD_PRODUCT_TYPE = executable
REQ_SRCS           = $(MODULES)

USER_SRCS =

USER_OBJS      = $(addsuffix .obj, $(basename $(USER_SRCS)))
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

SRCS = $(REQ_SRCS)

OBJS      = $(addsuffix .obj, $(basename $(SRCS))) $(USER_OBJS)
LINK_OBJS = $(addsuffix .obj, $(basename $(SRCS))) $(LOCAL_USER_OBJS)

#--------------------------- Link flags & libraries ----------------------------

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LDFLAGS = -s -L$(LIB)
else
LDFLAGS = -L$(LIB)
endif

#------------------------- Additional Libraries -------------------------------

LIBS =


LIBMWIPP = $(MATLAB_ROOT)\lib\win64\libmwipp.lib
LIBS +=  $(S_FUNCTIONS_LIB) $(LIBMWIPP)
LIBS += $(MATLAB_ROOT)\sys\lcc64\lcc64\lib64\ws2_32.lib
LIBS += $(MATLAB_ROOT)\sys\lcc64\lcc64\lib64\mswsock.lib 

#--------------------------------- Rules ---------------------------------------
$(PRODUCT) : $(OBJS) $(LIBS) $(MODELREF_LINK_LIBS)
	$(BIN_SETTING) @$(CMD_FILE) @$(MODELREF_LINK_RSPFILE) \
		$(LIBS) $(SYSTEM_LIBS)
	@cmd /C "echo $(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@"

%.obj : %.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.o : %.cpp
	$(CPP) -c $(CPPFLAGS)$(GCC_WALL_FLAG)  "$<"

%.obj : %.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : %.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) -c -Fo$(@F) -I$(RELATIVE_PATH_TO_ANCHOR)/$(<F:.c=cn_rtw) $(CFLAGS)  $<

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CC) -c -Fo$(@F) -I$(RELATIVE_PATH_TO_ANCHOR)/$(<F:.c=cn_rtw) $(CFLAGS)  $<

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.C
	$(CC) -c -Fo$(@F) -I$(RELATIVE_PATH_TO_ANCHOR)/$(<F:.c=cn_rtw) $(CFLAGS)  $<

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.CPP
	$(CC) -c -Fo$(@F) -I$(RELATIVE_PATH_TO_ANCHOR)/$(<F:.c=cn_rtw) $(CFLAGS)  $<

%.obj : $(MATLAB_ROOT)/rtw/c/raccel/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/raccel/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/rapid/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/rapid/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

simulink_solver_api.obj : $(MATLAB_ROOT)/simulink/include/simulink_solver_api.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

# Additional sources

%.obj : $(START_DIR)/slprj/raccel/untitled/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/rtiostreamtcpip/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

rt_logging.obj : $(MATLAB_ROOT)\rtw\c\src/rt_logging.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src/rt_logging.c

raccel_main_new.obj : $(MATLAB_ROOT)\rtw\c\raccel/raccel_main_new.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\raccel/raccel_main_new.c

raccel_sup.obj : $(MATLAB_ROOT)\rtw\c\raccel/raccel_sup.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\raccel/raccel_sup.c

raccel_mat.obj : $(MATLAB_ROOT)\rtw\c\raccel/raccel_mat.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\raccel/raccel_mat.c

simulink_solver_api.obj : $(MATLAB_ROOT)\simulink\include/simulink_solver_api.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\simulink\include/simulink_solver_api.c

raccel_utils.obj : $(MATLAB_ROOT)\rtw\c\src\rapid/raccel_utils.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\rapid/raccel_utils.c

common_utils.obj : $(MATLAB_ROOT)\rtw\c\src\rapid/common_utils.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\rapid/common_utils.c

ext_svr.obj : $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/ext_svr.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/ext_svr.c

updown.obj : $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/updown.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/updown.c

ext_work.obj : $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/ext_work.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/ext_work.c

rtiostream_interface.obj : $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/rtiostream_interface.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\rtw\c\src\ext_mode\common/rtiostream_interface.c

rtiostream_tcpip.obj : $(MATLAB_ROOT)\toolbox\coder\rtiostream\src\rtiostreamtcpip/rtiostream_tcpip.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $(MATLAB_ROOT)\toolbox\coder\rtiostream\src\rtiostreamtcpip/rtiostream_tcpip.c

rtiostream_utils.obj : D:\MATLAB\R2019a\toolbox\coder\rtiostream\src\utils/rtiostream_utils.c
	$(CC) -c -Fo$(@F) $(CFLAGS) D:\MATLAB\R2019a\toolbox\coder\rtiostream\src\utils/rtiostream_utils.c



%.obj : $(START_DIR)/slprj/raccel/untitled/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/simulink/src/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/rtiostreamtcpip/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils/%.C
	$(CC) -c -Fo$(@F) $(CFLAGS) $<



%.obj : $(START_DIR)/slprj/raccel/untitled/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/rtiostreamtcpip/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils/%.cpp
	$(CC) -c -Fo$(@F) $(CFLAGS) $<



%.obj : $(START_DIR)/slprj/raccel/untitled/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/simulink/src/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/rtiostreamtcpip/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils/%.CPP
	$(CC) -c -Fo$(@F) $(CFLAGS) $<



lccstub.obj : $(LCC)/mex/lccstub.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LCC)/mex/lccstub.c -o ./lccstub.obj

# Libraries:





#----------------------------- Dependencies ------------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw
