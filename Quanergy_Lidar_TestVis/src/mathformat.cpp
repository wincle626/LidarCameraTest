/*
 * mathformat.cpp
 *
 *  Created on: 29 May 2018
 *      Author: Yun Wu
 */

#include "mathformat.hpp"

int byte2int(char *bytes){
	/*unsigned int bytesuint = ((bytes[3]<<24)
						| (bytes[2]<<16)
						| (bytes[1]<<8)
						| bytes[0]);
	int bytesfloat = *(int *) & bytesuint;*/
	int bytesint = *(int*)(bytes);
	return bytesint;
}

float byte2float(char *bytes){
	/*unsigned int bytesuint = ((bytes[3]<<24)
						| (bytes[2]<<16)
						| (bytes[1]<<8)
						| bytes[0]);
	float bytesfloat = *(float *) & bytesuint;*/
	float bytesfloat = *(float*)(bytes);
	return bytesfloat;
}


void int2byte(int bytesint, char bytes[4]){
	/*unsigned int bytesuint = *(unsigned int *) & bytesfloat;
	bytes[0] = bytesuint & 0x0f;
	bytes[1] = (bytesuint>>8) & 0x0f;
	bytes[2] = (bytesuint>>16) & 0x0f;
	bytes[3] = (bytesuint>>24) & 0x0f;*/
	*(int*)(bytes) = bytesint;
}


void float2byte(float bytesfloat, char bytes[4]){
	/*unsigned int bytesuint = *(unsigned int *) & bytesfloat;
	bytes[0] = bytesuint & 0x0f;
	bytes[1] = (bytesuint>>8) & 0x0f;
	bytes[2] = (bytesuint>>16) & 0x0f;
	bytes[3] = (bytesuint>>24) & 0x0f;*/
	*(float*)(bytes) = bytesfloat;
}
