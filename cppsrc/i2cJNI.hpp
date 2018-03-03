/*
 * i2cJNI.hpp
 *
 *  Created on: Apr 15, 2015
 *      Author: harold
 */

#ifndef I2CJNI_HPP_
#define I2CJNI_HPP_

#include "jni_md.h"
#include "jni.h"

extern "C" /* specify the C calling convention */{
//Redifined
	jint Java_edu_fiu_cate_rasp_I2C_open(JNIEnv *env, jobject obj, jchar bus);
	jint Java_edu_fiu_cate_rasp_I2C_setSlaveAddress(JNIEnv *env, jobject obj, jint bus, jlong addr);
//End Redifined

//	jint Java_edu_fiu_cate_rasp_I2C_open(JNIEnv *env, jobject obj, jchar bus, jchar addr);

	// These functions return -1 on error, otherwise return the number of bytes read/written.
	// To perform a 'repeated start' use the i2c_write_read function which can write some
	// data and then immediately read data without a stop bit in between.
	jint Java_edu_fiu_cate_rasp_I2C_write(JNIEnv *env, jobject obj, jint handle, jbyteArray buf);

	jbyteArray Java_edu_fiu_cate_rasp_I2C_read(JNIEnv *env, jobject obj, jint handle, jint lenght);

	jbyteArray Java_edu_fiu_cate_rasp_I2C_writeRead(JNIEnv *env, jobject obj, jint handle, jbyte addr, jbyteArray buf_w, jint len_r);

	jint Java_edu_fiu_cate_rasp_I2C_writeIgnoreNack(JNIEnv *env, jobject obj, jint handle, jbyte addr, jbyteArray buf);

	jbyteArray Java_edu_fiu_cate_rasp_I2C_readNoAck(JNIEnv *env, jobject obj, jint handle, jbyte addr, jint lenght);

	jint Java_edu_fiu_cate_rasp_I2C_writeByte(JNIEnv *env, jobject obj, jint handle, jbyte val);

	jint Java_edu_fiu_cate_rasp_I2C_readByte(JNIEnv *env, jobject obj, jint handle);

	// These functions return -1 on error, otherwise return 0 on success
	jint Java_edu_fiu_cate_rasp_I2C_close(JNIEnv *env, jobject obj, jint handle);

}

#endif /* I2CJNI_HPP_ */
