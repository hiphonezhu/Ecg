/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <stdio.h>
#include "md5.h"
/* Header for class com_hiphone_offlinemap_CompactUtil */

#ifndef _Included_com_hiphone_offlinemap_CompactUtil
#define _Included_com_hiphone_offlinemap_CompactUtil
#ifdef __cplusplus
extern "C" {
#endif
/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/HelloJni/HelloJni.java
 */
char *my_strcat(const char *src1, const char *src2)
{
	char *pc=(char *)malloc(strlen(src1) + strlen(src2) + 1);
    size_t i,j;
    for (i = 0; src1[i] != '\0'; i++)
        pc[i] = src1[i];
    for (j = 0; src2[j] != '\0'; j++)
        pc[strlen(src1) + j] = src2[j];
    pc[i+j] = '\0';
    return pc;
}

jboolean Java_com_nju_ecg_service_EcgApp_isDeviceAuthorized(JNIEnv* env, jobject thiz, jstring deviceId, jstring authorizedDocumentPath)
{
	const char* strDeviceId = (*env)->GetStringUTFChars(env, deviceId, 0);
	const char* strAuthorizedDocumentPath = (*env)->GetStringUTFChars(env, authorizedDocumentPath, 0);
	// 设备标识需要连接一个秘密的字符串
	const char* security = "-nju_ecg";
	char* s = my_strcat(strDeviceId, security);
	// 生成MD5校验值，MD5结果全部使用小写
	MD5_CTX md5c;
	MD5Init(&md5c);
	MD5Update(&md5c, s, strlen(s));
	unsigned char ss[16];
	MD5Final(ss, &md5c);
	// 检查MD5校验是不是满足，如果不满足则立即返回，不进行后续处理
	int valid = 0;
	FILE* fValid;
	if ((fValid = fopen(strAuthorizedDocumentPath, "rb")) != NULL) {
		char str[32];
		fread(str, 32, 1, fValid);
		int i;
		int hasError = 0;
		for (i = 0; i < 16; i++) {
			unsigned int s1 = ss[i];
			int s2 = str[2 * i];
			if (s2 >= 48 && s2 <= 57)
			s2 -= 48;
			else if (s2 >= 97 && s2 <= 102)
			s2 -= 87;
			int s3 = str[2 * i + 1];
			if (s3 >= 48 && s3 <= 57)
			s3 -= 48;
			else if (s3 >= 97 && s3 <= 102)
			s3 -= 87;
			if (s1 != 16 * s2 + s3) {
				hasError = 1;
				break;
			}
		}
		if (hasError == 0) {
			valid = 1;
		}
	}
	unsigned char b = 0;
	if (valid == 1) {
		b = 1;
	}
	else {
		b = 0;
	}
	if (fValid != NULL) {
		fclose(fValid);
	}
	return (jboolean) b;
}
#ifdef __cplusplus
}
#endif
#endif
