LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DDEBUG

LOCAL_C_INCLUDES := \
	external/tslib/ \
	external/tslib/src \
	external/tslib/android

LOCAL_SRC_FILES := \
	ts_attach.c ts_close.c ts_config.c \
	ts_fd.c ts_load_module.c ts_open.c ts_read.c \
	ts_parse_vars.c ts_read_raw_module.c ts_read_raw.c ts_error.c \
	../android/CalibrateTouchScreen.c

LOCAL_MODULE := libtslib

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libdl libcutils

LOCAL_C_INCLUDES += dalvik/libnativehelper/include/nativehelper

LOCAL_LDLIBS += -lpthread

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

# ----------- For TS_PRINT ---------------------

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := \
	external/tslib/ \
	external/tslib/src \
	external/tslib/tests/ \
	external/tslib/android

LOCAL_SRC_FILES := ../tests/ts_print.c

LOCAL_MODULE := tsprint

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libtslib libdl

# ----------- For TS_TEST ------------------------

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := \
	external/tslib/ \
	external/tslib/src \
	external/tslib/tests/ \
	external/tslib/android

LOCAL_SRC_FILES := ../tests/ts_test.c

LOCAL_MODULE := tstest

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libtslib libdl libcutils

# ----------- For TEST_UTILS ---------------------

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := \
	external/tslib/ \
	external/tslib/src \
	external/tslib/tests/ \
	external/tslib/android

LOCAL_SRC_FILES := ../tests/testutils.c

LOCAL_MODULE := tsutils

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libtslib libdl

# ----------- For TS_CALIBRATE -------------------

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := \
	external/tslib/ \
	external/tslib/src \
	external/tslib/tests/ \
	external/tslib/android

LOCAL_C_INCLUDES += dalvik/libnativehelper/include/nativehelper

LOCAL_SRC_FILES := ../android/CalibrateTouchScreen.c

LOCAL_MODULE := tscalib

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libtslib libdl libcutils

# ----------- For TS.CONF -------------------

include $(CLEAR_VARS)

LOCAL_SRC_FILES := ../ts.conf

LOCAL_BUILT_MODULE_STEM := ts.conf

LOCAL_MODULE_SUFFIX := $(suffix ts.conf)

LOCAL_MODULE := $(basename ts.conf)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE_CLASS := ETC

LOCAL_MODULE_PATH := $(TARGET_OUT)

include $(BUILD_PREBUILT)
