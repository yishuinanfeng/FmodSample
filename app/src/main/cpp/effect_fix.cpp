//
// Created by Administrator on 2019/3/30.
//
#include <jni.h>
#include <common.h>
#include "inc/fmod.hpp"
#include <stdlib.h>
#include <android/log.h>
#include <unistd.h>

#define NORMAL_MODE 0
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);


#ifdef __cplusplus
extern "C" {
#endif

using namespace FMOD;

JNIEXPORT void JNICALL Java_com_nanfeng_fmoddemo_EffectUtil_fix
        (JNIEnv *env, jclass jcls, jstring path_jstring, jint type) {
    System *system;
    Sound *sound;
    Channel *channel;

    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);

    const char *path = env->GetStringUTFChars(path_jstring, NULL);

    //FMOD_DEFAULT会出问题?
    system->createSound(path, FMOD_DEFAULT, NULL, &sound);

    switch (type) {
        case NORMAL_MODE:
            LOGI("%s",path);
            system->playSound(sound, 0, false, &channel);
            LOGI("%s","fix normal");
            break;

        default:
            break;
    }

    system->update();

    usleep(5000*1000);
    env->ReleaseStringUTFChars(path_jstring, path);

    sound->release();
    system->close();
    system->release();
}

#ifdef __cplusplus
}
#endif