/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_eyer_eyerplayer_EyerPlayerJNI */

#ifndef _Included_com_eyer_eyerplayer_EyerPlayerJNI
#define _Included_com_eyer_eyerplayer_EyerPlayerJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_eyer_eyerplayer_EyerPlayerJNI
 * Method:    player_init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1init
  (JNIEnv *, jclass);

/*
 * Class:     com_eyer_eyerplayer_EyerPlayerJNI
 * Method:    player_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyerplayer_EyerPlayerJNI
 * Method:    player_setsurface
 * Signature: (JLandroid/view/Surface;)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1setsurface
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     com_eyer_eyerplayer_EyerPlayerJNI
 * Method:    player_open
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1open
  (JNIEnv *, jclass, jlong, jstring);

#ifdef __cplusplus
}
#endif
#endif
