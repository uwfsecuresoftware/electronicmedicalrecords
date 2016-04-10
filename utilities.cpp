#include "headers/utilities.h"

void Utility::zeroArray(int target[]) {
	int length = sizeof(*target) / sizeof(int);
	
	int i = 0;
	for(i = 0; i < length; i++) {
		target[i] = 0;
	}
}

void Utility::zeroArray(char *& target) {
	int length = sizeof(*target) / sizeof(char);
	
	int i = 0;
	for(i = 0; i < length; i++) {
		target[i] = 0;
	}
}