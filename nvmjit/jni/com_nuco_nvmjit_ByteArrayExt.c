#include "com_nuco_nvmjit_ByteArrayExt.h"

JNIEXPORT void JNICALL Java_com_nuco_nvmjit_ByteArrayExt_copyToJNI
	(JNIEnv *env, jclass cls, jlong cptr, jbyteArray arr)
{
	// convert into a pointer
	jbyte *p = (jbyte *)cptr;

	// copy
	jint len = (*env)->GetArrayLength(env, arr);
	(*env)->GetByteArrayRegion(env, arr, 0, len, p);
}

JNIEXPORT jbyteArray JNICALL Java_com_nuco_nvmjit_ByteArrayExt_copyFromJNI
	(JNIEnv *env, jclass clas, jlong cptr, jint size)
{
	// convert into a pointer
	jbyte *p = (jbyte *)cptr;

	// create a java array, which will be managed by garbage collector.
	jbyteArray arr = (*env)->NewByteArray(env, size);

	// copy
	(*env)->SetByteArrayRegion(env, arr, 0, size, p);

	return arr;
}
