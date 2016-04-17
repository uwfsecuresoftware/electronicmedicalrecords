#include "utility.h"
#include <stdio.h>

void initializeString(char * string, size_t stringSize) {
	int i = 0;
	for(i = 0; i < stringSize; i++) {
		string[i] = '\0';
	}
}

void generateUUID(char * uuid) {
	if(sizeof(uuid) < 33) {
		uuid = NULL;
		return;
	}
	
	char data[16];
	initializeString(data, 16);
	
	FILE *fp;
	fp = fopen("/dev/urandom", "r");
	fread(&data, 1, 16, fp);
	fclose(fp);
	
	char buffer[2];
	initializeString(uuid, 33);
	initializeString(buffer, 2);
	
	int i = 0;
	for(i = 0; i < 16; i++) {
		snprintf(buffer, 2, "%02X", data[i]);
		strncpy(uuid, buffer, 2);
	}
}