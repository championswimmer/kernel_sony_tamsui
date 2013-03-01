# /system/bin/busybox
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := busybox
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/bin

include $(BUILD_PREBUILT)

TOOLS := \
         swapon   \
         swapoff  \
         mkswap   \
         mknod

# Make #!/system/bin/busybox launchers for each tool.
SYMLINKS := $(addprefix $(TARGET_OUT)/bin/,$(TOOLS))
$(SYMLINKS): BUSYBOX_BINARY := $(LOCAL_MODULE)
$(SYMLINKS): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Busybox Symlink: $@ -> $(BUSYBOX_BINARY)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf $(BUSYBOX_BINARY) $@

ALL_DEFAULT_INSTALLED_MODULES += $(SYMLINKS)

# We need this so that the installed files could be picked up based on the local module name
ALL_MODULES.$(LOCAL_MODULE).INSTALLED := $(ALL_MODULES.$(LOCAL_MODULE).INSTALLED) $(SYMLINKS)
    
