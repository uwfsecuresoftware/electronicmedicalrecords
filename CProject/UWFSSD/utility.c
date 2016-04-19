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

void parseCSV(char * line, char ** csvData) {
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
			continue;
		}
		if(i >= 0 && i < maxLength) {
			strncat(buffer, line[i], 1);
		}
	}
}

int _isLeapYear(int year) {
	if(year % 4 == 0) {
		if(year % 100 == 0) {
			if(year % 400 == 0) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 1;
		}
	}
	else {
		return 0;
	}
}

long convertToTimestamp(int month, int day, int year, int hours, int minutes, int seconds) {
	long timestamp = 0;
	
	//Number of years since 1970 * number of seconds in a year (with no leap day)
	timestamp += ((year - 1) - 1970) * 31536000;
	
	//Calculates the number of leap days that have happened so far
	if(_isLeapYear(year)) {
		timestamp += (((year - 1972) - ((year - 1972) % 4)) / 4) * 86400;
	}
	else {
		timestamp += ((((year - 1972) - ((year - 1972) % 4)) / 4) + 1) * 86400;
	}
	
	int i = 0;
	for(i = 0; i < month; i++) {
		if(i = month - 1) {
			break;
		}
		
		switch(i) {
			case 0:
			case 2:
			case 4:
			case 6:
			case 7:
			case 9:
			case 11:
				timestamp += 31 * 86400;
				break;
			case 3:
			case 5:
			case 8:
			case 10:
				timestamp += 30 * 86400;
				break;
			case 1:
				if(_isLeapYear(year)) {
					timestamp += 29 * 86400;
				}
				else {
					timestamp += 28 * 86400;
				}
				break;
			default:
				break;
		}
	}
	
	timestamp += day * 86400;
	timestamp += hours * 60 * 60;
	timestamp += minutes * 60;
	timestamp += seconds;
	
	return timestamp;
}