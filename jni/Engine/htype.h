#pragma once

#ifndef  _WIN32
#define _ANDROID_
#else
#define  LOGD(...) 
#define  LOGI(...) 
#endif // ! _WIN32

#ifdef  _ANDROID_
#include <GLES2/gl2.h>
#include <GLES/glext.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define  LOG_TAG    "lwmAndroidJNI"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#else
#include <windows.h>
#define GLEW_STATIC
#include "glew.h"
#endif

#include "glm/mat4x4.hpp"
#include "glm/vector_relational.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#ifndef GRAPHIC_API
#if defined(_WIN32)
#ifdef GRAPHIC_EXPORTS
#define GRAPHIC_API __declspec(dllexport)
#pragma  comment(lib,"GLEW_190.lib")
#pragma  comment(lib,"opengl32.lib")
#pragma  comment(lib,"glu32.lib")
#else
#define GRAPHIC_API __declspec(dllimport)
#endif
#else// 其他平台都是静态库
#define GRAPHIC_API
#endif
#endif
