MK_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MK_DIR := $(dir $(MK_PATH))

# Inlude and re-export  
include $(MK_DIR)/config.mk

# Build Static Lib
sharedLibName := $(SHARED_LIB_NAME)
staticLibName := $(STATIC_LIB_NAME)

cppfiles := $(shell realpath --relative-to=$(MK_DIR) \
$(shell find $(MK_DIR) -type f -name "*.cpp"))



INC_DIRS = $(MK_DIR)
INC_FLAGS=$(patsubst %, -I%, $(INC_DIRS))

extraCPPFLAGS := -D_DEFAULT_SOURCE -D_FILE_OFFSET_BITS=64 $(INC_FLAGS)
extraCFLAGS := -fPIC -march=native -funroll-loops -ftree-vectorize -fno-inline -fstack-protector-all $(INC_FLAGS)