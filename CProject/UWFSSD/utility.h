#ifndef UTILITY_H
#define UTILITY_H

void initializeString(char * string, int stringLength);
void generateUUID(char * uuid);
void parseCSV(char * line, char csvData[10][50]);
long convertToTimestamp(int month, int day, int year, int hours, int minutes, int seconds);

#endif