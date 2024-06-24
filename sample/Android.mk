LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_CPP_EXTENSION := .cpp

LOCAL_MODULE    := HMI  

PATH = $(LOCAL_PATH)/..engine

LOCAL_C_INCLUDES := $(PATH)/include \
					$(PATH)/include/base \
					$(PATH)/include/graphic \
					$(PATH)/includeengine \
					$(TINMYXML_INCLUDE_PATH) \
					$(SKIA_INCLUDE_PATH) \
					$(SKIA_INCLUDE_PATH)/config \
					$(SKIA_INCLUDE_PATH)/core \
					$(SKIA_INCLUDE_PATH)/utils \
					$(SKIA_INCLUDE_PATH)/effects \
					$(SKIA_INCLUDE_PATH)/images \
					$(SKIA_INCLUDE_PATH)/lazy \
					$(BOOST_INCLUDE_PATH)

LOCAL_CFLAGS := $(PUBLIC_CFLAFS)

CODE_SOURCE := HelloGLACIER

LOCAL_SRC_FILES +=	$(CODE_SOURCE)/GlacierMainView.cpp \
					$(CODE_SOURCE)/GLACIERApp.cpp \
					$(CODE_SOURCE)/GLACIERApp_android.cpp
					
					

include $(BUILD_STATIC_LIBRARY)
