/*
 * i2cJNI.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: harold
 */

#include "i2cJNI.hpp"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" /* specify the C calling convention */{

//Redifined
	jint Java_edu_fiu_cate_rasp_I2C_open(JNIEnv *env, jobject obj, jchar bus){
		char filename[16];
		sprintf(filename,"/dev/i2c-%d", bus);
		return open(filename,O_RDWR);
	}

	jint Java_edu_fiu_cate_rasp_I2C_setSlaveAddress(JNIEnv *env, jobject obj, jint bus, jlong addr){
		return ioctl(bus, I2C_SLAVE, addr);
	}
//End Redifined

//	jint Java_edu_fiu_cate_rasp_I2C_open(JNIEnv *env, jobject obj, jchar bus, jchar addr){
//		return i2c_open(bus,addr);
//	}

	// These functions return -1 on error, otherwise return the number of bytes read/written.
	// To perform a 'repeated start' use the i2c_write_read function which can write some
	// data and then immediately read data without a stop bit in between.
	jint Java_edu_fiu_cate_rasp_I2C_write(JNIEnv *env, jobject obj, jint handle, jbyteArray buf){
		jint length = env->GetArrayLength(buf);
		jbyte* w_buf = env->GetByteArrayElements(buf, NULL);
		jint r = write(handle, (unsigned char*)w_buf, length);
		env->ReleaseByteArrayElements(buf, w_buf, 0);
		return r;
	}

	jbyteArray Java_edu_fiu_cate_rasp_I2C_read(JNIEnv *env, jobject obj, jint handle, jint lenght){
		jbyteArray read_buf = env->NewByteArray((jsize)lenght);
		jbyte* r_buf = env->GetByteArrayElements(read_buf, NULL);
		read(handle, (unsigned char*)r_buf, lenght);
		env->ReleaseByteArrayElements(read_buf, r_buf, 0);
		return read_buf;
	}

	jbyteArray Java_edu_fiu_cate_rasp_I2C_writeRead(JNIEnv *env, jobject obj, jint handle, jbyte addr, jbyteArray buf_w, jint len_r){
		jint len_w = env->GetArrayLength(buf_w);
		jbyte* w_buf = env->GetByteArrayElements(buf_w, NULL);
		jbyteArray read_buf = env->NewByteArray((jsize)len_r);
		jbyte* r_buf = env->GetByteArrayElements(read_buf, NULL);
		struct i2c_rdwr_ioctl_data msgset;
		struct i2c_msg msgs[2];
		msgs[0].addr=addr;
		msgs[0].len=len_w;
		msgs[0].flags=0;
		msgs[0].buf=(unsigned char*)w_buf;
		msgs[1].addr=addr;
		msgs[1].len=len_r;
		msgs[1].flags=1;
		msgs[1].buf=(unsigned char*)r_buf;
		msgset.nmsgs=2;
		msgset.msgs=msgs;
		ioctl(handle,I2C_RDWR,(unsigned long)&msgset);
		env->ReleaseByteArrayElements(read_buf, r_buf, 0);
		env->ReleaseByteArrayElements(buf_w, w_buf, 0);
		return read_buf;
	}

	jint Java_edu_fiu_cate_rasp_I2C_writeIgnoreNack(JNIEnv *env, jobject obj, jint handle, jbyte addr, jbyteArray buf){
		jint length = env->GetArrayLength(buf);
		jbyte* w_buf = env->GetByteArrayElements(buf, NULL);
		struct i2c_rdwr_ioctl_data msgset;
		struct i2c_msg msgs[1];
		msgs[0].addr=addr;
		msgs[0].len=length;
		msgs[0].flags=0 | I2C_M_IGNORE_NAK;
		msgs[0].buf=(unsigned char*)w_buf;
		msgset.nmsgs=1;
		msgset.msgs=msgs;
		jint r = ioctl(handle,I2C_RDWR,(unsigned long)&msgset);
		env->ReleaseByteArrayElements(buf, w_buf, 0);
		return r;
	}

	jbyteArray Java_edu_fiu_cate_rasp_I2C_readNoAck(JNIEnv *env, jobject obj, jint handle, jbyte addr, jint lenght){
		jbyteArray read_buf = env->NewByteArray((jsize)lenght);
		jbyte* r_buf = env->GetByteArrayElements(read_buf, NULL);
		struct i2c_rdwr_ioctl_data msgset;
		struct i2c_msg msgs[1];
		msgs[0].addr=addr;
		msgs[0].len=lenght;
		msgs[0].flags=I2C_M_RD | I2C_M_NO_RD_ACK;
		msgs[0].buf=(unsigned char*)r_buf;
		msgset.nmsgs=1;
		msgset.msgs=msgs;
		ioctl(handle,I2C_RDWR,(unsigned long)&msgset);
		env->ReleaseByteArrayElements(read_buf, r_buf, 0);
		return read_buf;
	}

	jint Java_edu_fiu_cate_rasp_I2C_writeByte(JNIEnv *env, jobject obj, jint handle, jbyte val){
		return write(handle, &val, 1);
	}

	jint Java_edu_fiu_cate_rasp_I2C_readByte(JNIEnv *env, jobject obj, jint handle){
		jint val;
		if(read(handle, (unsigned char*)&val, 1)<0){
			return -1;
		}
		return val;
	}

	// These functions return -1 on error, otherwise return 0 on success
	jint Java_edu_fiu_cate_rasp_I2C_close(JNIEnv *env, jobject obj, jint handle){
		return close(handle);
	}

}
