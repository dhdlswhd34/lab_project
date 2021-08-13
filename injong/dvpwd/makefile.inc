################################################################################
#                                                                              #
#                                  DIRECTORY                                   #
#                                                                              #
################################################################################
VERSION         = 2.0.0

RELEASE         = yes
#WIN32           = yes
LINUX           = yes

#OS = LINUX
#SHARED_LIB     = yes
#VERSION_OUT    = yes 
#DEPLOY_DIR      = ../

LICENSE ?= no

CROSS_COMPILE   ?= no

#ARCH_TYPE     ?= WIN32
##ARCH_TYPE     = WINCE
ARCH_TYPE     ?= LINUX32
#ARCH_TYPE     ?= LINUX_ARM
#ARCH_TYPE     ?= LINUX_ARMHF



################################################################################
################################################################################
################################################################################
#                                                                              #
#                                  WIN32                                       #
#                                                                              #
################################################################################
DDK_DIR     = C:\WINDDK\2600.1106
VS_DIR      = C:\Program Files\Microsoft Visual Studio 10.0
SDK_DIR     = C:\Program Files\Microsoft SDKs\Windows\v7.0A

VC_DIR      = $(VS_DIR)\VC

VC_BIN      = $(VC_DIR)\bin
VC_LIB      = "$(VC_DIR)\lib"
VC_INC      = "$(VC_DIR)\include"

SDK_LIB     = "$(SDK_DIR)\Lib"
SDK_INC     = "$(SDK_DIR)\include"

DDK_BIN     = $(DDK_DIR)\bin\x86
DDK_LIB     = $(DDK_DIR)\lib
DDK_INC     = $(DDK_DIR)\inc

VC_BIN      = $(DDK_BIN)
#VC_LIB      = $(DDK_LIB)
#VC_INC      = $(DDK_INC)

################################################################################
#                                                                              #
#                                  COMMANDS                                    #
#                                                                              #
################################################################################
SUFFIX    = .dll
CC        = "$(VC_BIN)\cl.exe"
LINK      = "$(VC_BIN)\link.exe"
LIB       = "$(VC_BIN)\lib.exe"
MT        = "$(VC_BIN)\mt.exe"
MKDIR     = mkdir

################################################################################
#                                                                              #
#                                LIBRARAIES                                    #
#                                                                              #
################################################################################
VC_LIBS  =  msvcrt.lib \
						libcmt.lib \
						oldnames.lib

API_LIBS =  kernel32.lib \
						user32.lib \
						Uuid.Lib

NET_LIBS =  WS2_32.Lib \
						MsWSock.Lib \
						WSock32.Lib \
						WinInet.lib

ODBC_LIBS = odbc32.lib \
            odbccp32.lib

################################################################################
#                                                                              #
#                                  OPTIONS                                     #
#                                                                              #
################################################################################
DEFINITIONS = /D XWIN32 \
              /D _WINDOWS \
              /D _WINDLL \
              /D _MBCS
              #/D BSD_SOCKET \
              #/D POLLING
              #/D IOCP_SOCKET

COPT        = /FD \
							/W4 \
              /nologo \
              /c \
              /TP \
              /errorReport:prompt

API_OPT     = /MT

WINDOW_OPT  = /SUBSYSTEM:WINDOWS

LIB_OPT     = /OUT:$(_LIB)\$@.lib \
              /NOLOGO

DLL_OPT     = /OUT:$(_LIB)\$@.dll \
              /DLL \
              /MANIFEST \
							/MANIFESTFILE:$(RELEASE_DIR)\$@.dll.intermediate.manifest

EXE_OPT     = /OUT:$(_BIN)\$@.exe \
              /MANIFEST \
							/MANIFESTFILE:$(RELEASE_DIR)\$@.exe.intermediate.manifest

CFLAGS =      /Ox \
              /GL \
              /I $(VC_INC) \
							/I $(SDK_INC) \
              $(DEFINITIONS)


LINKER_OPT  = /INCREMENTAL:NO \
              /NOLOGO \
							/OPT:REF \
							/OPT:ICF \
							/LTCG \
							/MACHINE:X86 \
							/ERRORREPORT:PROMPT \
              /LIBPATH:$(VC_LIB) \
							/LIBPATH:$(SDK_LIB) \
							$(API_LIBS)

################################################################################
################################################################################
################################################################################
# PART I                                                                       #
#                                                                              #
# COMPILE OPTION                                                               #
################################################################################
ifeq ($(ARCH_TYPE), LINUX32)
TOOLCHAIN_PATH = /usr
endif
ifeq ($(ARCH_TYPE), LINUX64)
TOOLCHAIN_PATH = /usr
endif
ifeq ($(ARCH_TYPE), LINUX_ARM)
TOOLCHAIN_PATH = /usr/local/ext/toolchain/arm-linux-gnueabi/
endif
ifeq ($(ARCH_TYPE), LINUX_ARMHF)
TOOLCHAIN_PATH = /usr/local/ext/toolchain/arm-linux-gnueabihf/
endif
ifeq ($(ARCH_TYPE), ANDROID_NDK)
TOOLCHAIN_PATH = /usr/local/PROJECT/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86
endif

TOOLCHAIN_BIN  = $(TOOLCHAIN_PATH)/bin/

SYSTEM_ROOT = .

ifdef LINUX
ifeq ($(CROSS_COMPILE), yes)
ifeq ($(ARCH_TYPE), LINUX_ARM)
XCOMPILE- = arm-linux-gnueabi-
XTARGET   = arm
endif
ifeq ($(ARCH_TYPE), LINUX_ARMHF)
XCOMPILE- = arm-linux-gnueabihf-
XTARGET   = armhf
endif
ifeq ($(ARCH_TYPE), ANDROID_NDK)
XCOMPILE- = arm-linux-androideabi-
XTARGET   = androidndk
endif
else
ifeq ($(ARCH_TYPE), LINUX32)
XTARGET   = x32
endif
ifeq ($(ARCH_TYPE), LINUX64)
XTARGET   = x64
endif
TOOLCHAIN_BIN  = 
endif
endif


ifdef LINUX
CC     = $(TOOLCHAIN_BIN)$(XCOMPILE-)gcc
else
CC     = cl.exe
endif
AR     = $(TOOLCHAIN_BIN)$(XCOMPILE-)ar
AR_OPT = rcs
RANLIB = $(TOOLCHAIN_BIN)$(XCOMPILE-)ranlib

TOOLCHAIN_LIB = $(TOOLCHAIN_PATH)/lib

SRC_SUFFIX = .c

ifdef LINUX
OBJ_SUFFIX = .o
else
OBJ_SUFFIX = .obj
endif


ifdef SHARED_LIB
ifdef LINUX
LIB_SUFFIX = .so
else
LIB_SUFFIX = .dll
endif
else
ifdef LINUX
LIB_SUFFIX = .a
else
LIB_SUFFIX = .lib
endif
endif

ifdef RELEASE
COPT = -O2 -no-integrated-cpp
else
COPT = -g -ggdb -W -Wall -no-integrated-cpp
endif

ifeq ($(ARCH_TYPE), LINUX32)
COPT += -m32 -Dx32
endif

ifeq ($(ARCH_TYPE), LINUX64)
COPT += -m64 -Dx64
endif

ifeq ($(ARCH_TYPE), LINUX_ARM)
xCOPT += -mbig-endian
endif

ifeq ($(ARCH_TYPE), LINUX_ARMHF)
xCOPT += -mbig-endian
endif

ifdef LINUX
LIBS = -lnsl -lrt
else
LIBS = -lsocket -lnsl -lrt
endif

CPPLIBS = 

PTHREADLIB = -lpthread

RM = rm -rf
CP = cp -rf
MV = mv

GENLIB = -lm
CODECLIB = -lfaad -lfaac


################################################################################
# PART II                                                                      #
#                                                                              #
# DEFINITION                                                                   #
################################################################################
OS_TYPE  = -DLINUX
OS_TYPE  += -DBSD_SOCKET
OS_TYPE  += -DPOLLING
#OS_TYPE  += -DRTS
#OS_TYPE  += -DCONSOLE_PRINT
ifdef SHARED_LIB
OS_TYPE  += -DSHARED_LIB
else
OS_TYPE  += -DSTATIC_LIB
endif

OS  = $(OS_TYPE)

PLATFORM_TYPE = $(ARCH_TYPE)

################################################################################
# PART III                                                                     #
#                                                                              #
# DIRECTORIES                                                                  #
################################################################################
INC = inc
SRC = src
LIB = $(PLATFORM_TYPE)/lib
OBJ = $(PLATFORM_TYPE)/obj
BIN = $(PLATFORM_TYPE)/bin
COM = $(PLATFORM_TYPE)/coms

OSS_INC = -I/usr/lib/oss/include
CODEC_INC = -I/usr/local/AAC/include
CODEC_LIB = -L/usr/local/AAC/lib

################################################################################
# PART IV                                                                      #
#                                                                              #
# SHARED OBJECT                                                                #
################################################################################


################################################################################
# PART V                                                                       #
#                                                                              #
# SOURCE CONVERTING                                                            #
################################################################################
SRCS = $(foreach dir, . $(SRC), $(wildcard $(dir)/*$(SRC_SUFFIX)))
OBJS = $(foreach dir, . $(OBJ), $(wildcard $(dir)/*$(OBJ_SUFFIX)))
LIBS = $(foreach dir, . $(LIB), $(wildcard $(dir)/*$(LIB_SUFFIX)))

################################################################################
# PART VI                                                                      #
#                                                                              #
# OBJECT                                                                       #
################################################################################
%$(OBJ_SUFFIX) : $(SRC)/%$(SRC_SUFFIX)
	@echo "################################################################################"
	@echo "#  generate "$@
	@echo "################################################################################"
	$(RM) $(OBJ)/$@;
#	$(CC) -sysroot=$(TOOLCHAIN_PATH) -I$(INC) $(OS) $(COPT) -o $(OBJ)/$@ -fPIC -c $<;
	$(CC) -I$(INC) $(OS) $(COPT) -o $(OBJ)/$@ -fPIC -c $<;


################################################################################
# PART VII                                                                     #
#                                                                              #
# LIBRARY                                                                      #
################################################################################
%$(LIB_SUFFIX) : $(OBJS)
	@echo "################################################################################"
	@echo "#  generate "$@
	@echo "###############################################################################"
	$(RM) $(LIB)/$@;
ifdef VERSION_OUT
	$(RM) $(LIB)/$@.$(VERSION);
endif
ifdef SHARED_LIB
ifdef VERSION_OUT
	$(CC) -fPIC -shared -o $(LIB)/$@.$(VERSION) $^;
else
	$(CC) -shared -o $(LIB)/$@ $^;
endif
else
	$(AR) $(AR_OPT) $(LIB)/$@ $^;
	$(RANLIB) $(LIB)/$@;
endif
#	$(CP) $(LIB)/$@ $(BIN)

