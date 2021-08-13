include ./makefile.inc
################################################################################
# PART VIII                                                                    #
#                                                                              #
# ADDITIONAL INFO                                                              #
################################################################################
MTIF_PATH = $(shell pwd)/../..
APP_NAME = $(notdir $(shell pwd))
OUT_NAME = $(APP_NAME)

APP_SRC_PATH  = .
APP_SRC_PATH += src
APP_SRCS = $(sort $(foreach dir, $(APP_SRC_PATH), $(wildcard $(dir)/*$(SRC_SUFFIX))))
APP_INC += -Iinc
APP_INC += -I$(MTIF_PATH)/mtif/coms
ifeq ($(ARCH_TYPE), LINUX32)
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux/include
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux/include/openssl
endif
ifeq ($(ARCH_TYPE), LINUX_ARM)
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux-arm/include
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux-arm/include/openssl
endif
ifeq ($(ARCH_TYPE), LINUX_ARMHF)
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux-armhf/include
APP_INC += -I$(MTIF_PATH)/mtif/openssl/linux-armhf/include/openssl
endif

APP_LIB += -Xlinker --start-group
APP_LIB += $(MTIF_PATH)/mtif/coms/libmtif.$(XTARGET).a
APP_LIB += $(MTIF_PATH)/mtif/coms/libxmtif.$(XTARGET).a
APP_LIB += $(MTIF_PATH)/mtif/coms/libxutil.$(XTARGET).a
APP_LIB += $(MTIF_PATH)/mtif/coms/libxcore.$(XTARGET).a
ifeq ($(ARCH_TYPE), LINUX32)
APP_LIB += $(MTIF_PATH)/mtif/openssl/linux/lib/libssl.a
xAPP_LIB += $(MTIF_PATH)/mtif/openssl/linux/lib/libcrypto.a
endif
ifeq ($(ARCH_TYPE), LINUX_ARM)
APP_LIB += $(MTIF_PATH)/mtif/openssl/linux-arm/lib/libssl.a
xAPP_LIB += $(MTIF_PATH)/mtif/openssl/linux-arm/lib/libcrypto.a
endif
ifeq ($(ARCH_TYPE), LINUX_ARMHF)
APP_LIB += $(MTIF_PATH)/mtif/openssl/linux-armhf/lib/libssl.a
xAPP_LIB += $(MTIF_PATH)/mtif/openssl/linux-armhf/lib/libcrypto.a
endif
APP_LIB += -Xlinker --end-group
APP_LIB += -ldl -L$(TOOLCHAIN_LIB) -lgcc_s



COPT += -D$(APP_NAME)
COPT += -DUSE_EX=1
COPT += -DUSE_MTIF=1
COPT += -DUSE_SYSQUEUE=1

ifeq ($(ARCH_TYPE), LINUX32)
  COPT += -D_LITTLE_ENDIAN_
endif

ifeq ($(ARCH_TYPE), LINUX_ARM)
  COPT += -D_BIG_ENDIAN_
endif	

ifeq ($(ARCH_TYPE), LINUX_ARMHF)
  COPT += -D_BIG_ENDIAN_
endif	


################################################################################
# PART VIII                                                                    #
#                                                                              #
# COMPONENT                                                                    #
################################################################################
print:
	@echo $(EXT_INC)
	@echo $(EXT_LIB)

all : objs
	make $(OUT_NAME);

mtif_coms:
	\cp -rf $(ASEF_PATH)/appf/xNCTools/mtif    ./

xobjs:
	make $(subst $(SRC_SUFFIX),$(OBJ_SUFFIX),$(subst $(SRC)/, ,$(SRCS)));

objs:
	$(RM) $(OBJ)/$@;
ifdef SHARED_LIB
	$(CC) -I$(INC) $(OS) $(COPT) -DSINGLE_DLL \
	$(APP_INC) \
	-c $(APP_SRCS)
else
	$(CC) -I$(INC) $(OS) $(COPT) \
	$(APP_INC) \
	-c $(APP_SRCS)
endif
	$(MV) ./*$(OBJ_SUFFIX) $(OBJ);

% :
	@echo "################################################################################"
	@echo "#  Generate "$@
	@echo "################################################################################"
ifdef SHARED_LIB
	$(CC) -rdynamic -o $(BIN)/$@ $(SRC)/$@$(SRC_SUFFIX) \
	-DLINUX \
	-I$(INC) $(OS) $(COPT) $(PTHREADLIB) $(GENLIB) \
	$(MYSQL_CONFIG) \
	$(APP_INC) \
	$(APP_LIB)
else
	$(CC) -o $(BIN)/$@ $(OBJS) \
	-DLINUX \
	-I$(INC) $(OS) $(COPT) $(PTHREADLIB) $(GENLIB) \
	$(APP_INC) \
	$(APP_LIB)
endif

dir:
	mkdir -p $(PLATFORM_TYPE);
	mkdir -p $(OBJ);
	mkdir -p $(LIB);
	mkdir -p $(BIN);
	mkdir -p $(COM);
################################################################################
# PART IX                                                                      #
#                                                                              #
# REMOVE OBJECTS                                                               #
################################################################################

clean :
	@clear
	$(RM)  *.o core;
	$(RM)  $(OBJ)/*.o;
	$(RM)  $(BIN)/*;
ifdef VERSION_OUT
	$(RM)  $(LIB)/*$(LIB_SUFFIX).$(VERSION);
endif
	$(RM)  $(LIB)/*$(LIB_SUFFIX);
ifdef DEPLOY_DIR
	$(RM)  $(DEPLOY_DIR)/core;
	$(RM)  $(DEPLOY_DIR)/$(BIN)/*;
endif

distclean:
	@clear
	$(RM)  *.o core;
	$(RM)  $(BIN)/*;
	$(RM)  $(OBJ)/*.o;
	$(RM)  $(LIB)/*.$(LIB_SUFFIX);

