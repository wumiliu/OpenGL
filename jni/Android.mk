LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := FreeImageStatic
LOCAL_SRC_FILES := libFreeImageStatic.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := Engine
LOCAL_C_INCLUDES   := $(LOCAL_PATH)/Engine\
 					$(LOCAL_PATH)/Engine/glm\
 					$(LOCAL_PATH)/Engine/BaseCode

LOCAL_SRC_FILES := Engine.cpp\
		Engine\OpenGLEngine.cpp\
		Engine\glShaderFactory.cpp\
		Engine\glMeshFactory.cpp\
		Engine\glRenderer.cpp\
		Engine\Texture.cpp\
		Engine\TextureMgr.cpp\
		Engine\GameManager.cpp\
		Engine\InputManager.cpp\
		Engine\ScrolRect.cpp\
		Engine\p3type.cpp


LOCAL_LDLIBS+= -L$(SYSROOT)/usr/lib -llog
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_SHARED_LIBRARIES := FreeImageStatic


include $(BUILD_SHARED_LIBRARY)
