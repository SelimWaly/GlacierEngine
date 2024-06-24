LOCAL_PATH := $(call my-dir)
##========================================================================
include $(CLEAR_VARS)
LOCAL_MODULE := skia_android
LOCAL_SRC_FILES := $(APP_PROJECT_PATH)/../../third_party/skia_android/libskia_android.so
THIRD_PATH := $(APP_PROJECT_PATH)/../third_party
SKIA_INCLUDE_PATH := $(THIRD_PATH)/skia_android/include
TINMYXML_INCLUDE_PATH := $(THIRD_PATH)/tinyxml
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS) # clear out the variables of the previous module
BOOST_INCLUDE_PATH := $(APP_PROJECT_PATH)/../third_party/boost/boost_1_51_0
STL_LIBS :=

PUBLIC_CFLAFS := -DANDROID_NDK -DKOTEI_LINUX -DLINUX -D__LINUX_CPL__ -DUNICODE -D_UNICODE \
       -DRE_LIB  -DZIP_DATA  -DRTIC_HANDLE \
       -D_FILE_OFFSET_BITS=64 -D_LARGE_FILE -DBOOST_SYSTEM_NO_DEPRECATED -D_LITTLE_ENDIAN\
        -fsigned-char -w -fpermissive

LOCAL_MODULE := glacier
SRC_ROOT := $(LOCAL_PATH)/../..
LOCAL_C_INCLUDES := $(BOOST_INCLUDE_PATH) \
					$(SKIA_INCLUDE_PATH) \
					$(SKIA_INCLUDE_PATH)/core \
					$(SKIA_INCLUDE_PATH)/config \
					$(SKIA_INCLUDE_PATH)/lazy \
					$(SRC_ROOT)/engine/include \
					$(SRC_ROOT)/engine/include/base \
					$(SRC_ROOT)/engine/include/graphic \
					$(SRC_ROOT)/engine/includeengine \
					$(SRC_ROOT)/engine/RenderingEngine \
					$(LOCAL_PATH)/android \

LOCAL_CFLAGS := $(PUBLIC_CFLAFS)					

LOCAL_SRC_FILES := MainActivity.cpp \
					AndroidMain.cpp \
					JNIRegistStaticMethod.cpp
					
LOCAL_STATIC_LIBRARIES := HMI GLACIER

LOCAL_SHARED_LIBRARIES := skia_android
LOCAL_LDLIBS := -llog -ljnigraphics
BOOST_LIB_PATH := $(LOCAL_PATH)/../../third_party/lib/boost_android/
LOCAL_LDFLAGS += $(BOOST_LIB_PATH)libboost_thread-gcc-mt-s-1_51.a \
 $(BOOST_LIB_PATH)libboost_timer-gcc-mt-s-1_51.a \
 $(BOOST_LIB_PATH)libboost_system-gcc-mt-s-1_51.a \
 $(BOOST_LIB_PATH)libboost_chrono-gcc-mt-s-1_51.a \
 $(BOOST_LIB_PATH)libboost_date_time-gcc-mt-s-1_51.a \
 $(STL_LIBS)

include $(BUILD_SHARED_LIBRARY)

ENGINE_PATH := $(LOCAL_PATH)/../../..engine-master
include $(call all-makefiles-under, $(ENGINE_PATH))
