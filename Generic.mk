LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := etk
LOCAL_LIBRARIES := linearmath

# with android we have no real choice ...
ifeq ("$(PLATFORM)","Android")
	LOCAL_LIBRARIES += libzip
else
	ifeq ("$(CONFIG_BUILD_LIBZIP)","y")
		LOCAL_LIBRARIES += libzip
	endif
endif


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

ifeq ($(DEBUG),1)
LOCAL_CFLAGS := -Wno-write-strings \
                -Wall
else
LOCAL_CFLAGS := -Wno-write-strings \
                -DMODE_RELEASE
endif


# load the common sources file of the platform
include $(LOCAL_PATH)/file.mk

LOCAL_SRC_FILES := $(FILE_LIST)





include $(BUILD_STATIC_LIBRARY)
