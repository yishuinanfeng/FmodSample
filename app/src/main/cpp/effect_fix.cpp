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
#define MODE_LUOLI  1
#define MODE_DASHU 2
#define MODE_JINGSONG  3
#define MODE_GAOGUAI  4
#define MODE_KONGLING 5



#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);


#ifdef __cplusplus
extern "C" {
#endif

using namespace FMOD;

JNIEXPORT void JNICALL Java_com_nanfeng_fmoddemo_EffectUtil_fix
        (JNIEnv *env, jclass jcls, jstring path_jstring, jint type) {
    System *system;
    Sound *sound;
    Channel *channel;
    float frequency = 0;
    DSP *dsp;
    bool isplay = true;

    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);

    const char *path = env->GetStringUTFChars(path_jstring, NULL);

    //FMOD_DEFAULT会出问题?
    system->createSound(path, FMOD_DEFAULT, NULL, &sound);

    switch (type) {
        case NORMAL_MODE:
            LOGI("%s", path);
            system->playSound(sound, 0, false, &channel);
            LOGI("%s", "fix normal");
            break;

        case MODE_LUOLI:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.0);
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0,dsp);
            break;

        case MODE_GAOGUAI:
            system->playSound(sound, 0, false, &channel);
            channel->getFrequency(&frequency);
            frequency = frequency *2;
            channel->setFrequency(frequency);
            break;

        default:
            system->playSound(sound, 0, false, &channel);
            break;
    }

    //真正播放声音
    system->update();

    while (isplay) {
        channel->isPlaying(&isplay);
        usleep(1000 * 1000);
    }

    env->ReleaseStringUTFChars(path_jstring, path);

    sound->release();
    system->close();
    system->release();
}

#ifdef __cplusplus
}
#endif