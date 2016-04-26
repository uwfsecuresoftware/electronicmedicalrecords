#include "utility.h"
#include <stdio.h>
#include <string.h>

void initializeString(char * string, int stringSize) {
	int i = 0;
	for(i = 0; i < stringSize; i++) {
		string[i] = '\0';
	}
}

void generateUUID(char * uuid) {

	char data[16];
	initializeString(data, 16);
	
	FILE *fp;
	fp = fopen("/dev/urandom", "r");
	if(fread(&data, 1, 16, fp) != 16) {
		//Reading error
	}
	fclose(fp);
	
	char buffer[3];
	initializeString(uuid, 33);
	initializeString(buffer, 3);
	
	int i = 0;
	for(i = 0; i < 16; i++) {
		snprintf(buffer, 3, "%02X", data[i]);
		strncat(uuid, buffer, 2);
	}
}

int getSizeOfString(char * string, int maxLength) {
        int i;
	for(i = 0; i < maxLength; i++) {
		if(string[i] == '\0') {
			return i + 1;
		}
	}
	return maxLength;
}

void parseCSV(char * line, char csvData[10][50]) {
	char buffer[50];
	
	initializeString(buffer, 50);
	
	const int maxLength = strnlen(line, 500);
	int i = 0;
	int currentField = 0;
	
	for(i = 0; i < maxLength; i++) {
		//End of the CSV field
		if(line[i] == ',' || line[i] == '\n' || line[i] == '\0' || i == (maxLength - 1)) {
			initializeString(csvData[currentField], 50);
			strncpy(csvData[currentField], buffer, 50);
			currentField++;
			initializeString(buffer, 50);
			continue;
		}
		if(i >= 0 && i < maxLength) {
			char temp[2];
			initializeString(temp, 2);
			temp[0] = line[i];
			
			strncat(buffer, temp, 1);
		}
	}
}