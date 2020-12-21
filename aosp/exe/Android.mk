# Copyright 2006-2014 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= main.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_CFLAGS := -Werror

LOCAL_MODULE := hello

include $(BUILD_EXECUTABLE)
