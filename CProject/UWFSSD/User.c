#include "User.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

PatientCacheT * patientCache = NULL;

PatientT * fetchPatient(char * uuid) {
	if(patientCache == NULL) {
		patientCache = malloc(sizeof(PatientCacheT));
		if(patientCache == NULL) {
			//malloc error
		}
		else {
			patientCache->item = NULL;
			patientCache->next = NULL;
		}
	}
	
	//First we need to search the cache for a proper user
	PatientCacheT * currentRecord = patientCache;
	
	while(true) {
		if(currentRecord->item == NULL) {
			//There is no record, ayyyyy
			break;
		}
		
		//Match found
		if(strncmp(currentRecord->item->uuid, uuid, 33)) {
			return currentRecord->item;
		}
	}
	//No record :c

	char fileName[45];
	initializeString(fileName, 45);
	strncpy(fileName, "records/", 8);
	strncpy(fileName, uuid, 32);
	FILE * userRecords = fopen(fileName, "r");
	
	char line[500];
	initializeString(line, 500);
	//First thing we wanna read in is the basic information about the user
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	
	PatientT * patient = malloc(sizeof(PatientT));
	
	if(patient == NULL) {
		//Error during malloc
	}
	
	if(feof(userRecords) && (line[0] == '\0' || line[0] == ' ' || line[1] == '\0')) {
		fclose(userRecords);
		return patient;
	}
	
	char csvData[10][50];
	parseCSV(line, csvData);
	
	strncpy(patient->firstName, csvData[0], 29);
	strncpy(patient->lastName, csvData[1], 29);
	patient->smokes = (strncmp(csvData[2], "1", 1) == 0) ? true : false;
	strncpy(patient->race, csvData[3], 29);
	strncpy(patient->gender, csvData[4], 29);
	
	int age = (int) strtol(csvData[5], NULL, 10);
	if(age == 0) {
		//Errored out during conversion
		printf("System errored during age import. Setting age to -1\n");
		age = -1;
	}
	patient->age = age;
	
	strncpy(patient->ssn, csvData[6], 10);
	strncpy(patient->dateOfBirth, csvData[7], 10);
	
	//-------------------------------------------------------------------------------
	//Insurance information
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	parseCSV(line, csvData);
	
	InsuranceT * insurance = malloc(sizeof(InsuranceT));
	
	if(insurance == NULL) {
		//Malloc error
	}
	
	strncpy(insurance->name, csvData[0], 40);
	strncpy(insurance->policyNumber, csvData[1], 30);
	
	patient->insurance = insurance;
	
	//--------------------------------------------------------------------------------
	//Immunization data
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	parseCSV(line, csvData);
	
	int numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System errored during Immunization import. Ignoring.");
		numberOfRecords = 0;
	}
	
	int i = 0;
	ImmunizationListT * lastRecordImmu = malloc(sizeof(ImmunizationListT));
	
	if(lastRecordImmu == NULL) {
		//Malloc error
	}
	
	ImmunizationListT * firstRecordImmu = lastRecordImmu;
	for(i = 0; i < numberOfRecords; i++) {
		if(fgets(line, 500, userRecords) == NULL) {
			//Error during reading
		}
		parseCSV(line, csvData);
		
		ImmunizationT * record = malloc(sizeof(ImmunizationT));
		
		if(record == NULL) {
			//Malloc error
		}
		
		strncpy(record->name, csvData[0], 40);
		strncpy(record->datePerformed, csvData[1], 20);
		strncpy(record->performingPerson, csvData[2], 33);
		
		lastRecordImmu->item = record;
		lastRecordImmu->next = malloc(sizeof(ImmunizationListT));
		
		if(lastRecordImmu->next == NULL) {
			//Malloc error
		}
		
		lastRecordImmu = lastRecordImmu->next;
	}
	
	patient->immunizations = firstRecordImmu;
	
	
	//--------------------------------------------------------------------------------
	//Medication data
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	parseCSV(line, csvData);
	
	numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System errored during Medication import. Ignoring.");
		numberOfRecords = 0;
	}
	
	MedicationListT * lastRecordMedi = malloc(sizeof(MedicationListT));
	
	if(lastRecordMedi == NULL) {
		//Malloc error
	}
	
	MedicationListT * firstRecordMedi = lastRecordMedi;
	for(i = 0; i < numberOfRecords; i++) {
		if(fgets(line, 500, userRecords) == NULL) {
			//Error during reading
		}
		parseCSV(line, csvData);
		
		MedicationT * record = malloc(sizeof(MedicationT));
		
		if(record == NULL) {
			//Malloc error
		}
		
		strncpy(record->name, csvData[0], 40);
		
		const int dosage = (int) strtol(csvData[1], NULL, 10);
		if(dosage == 0) {
			printf("System error during Medication import.");
			record->dosage = -1;
		}
		else {
			record->dosage = dosage;
		}
		strncpy(record->prescribingPerson, csvData[2], 33);
		
		lastRecordMedi->item = record;
		lastRecordMedi->next = malloc(sizeof(MedicationListT));
		
		if(lastRecordMedi->next == NULL) {
			//Malloc error
		}
		
		lastRecordMedi = lastRecordMedi->next;
	}
	
	patient->medications = firstRecordMedi;
	
	//---------------------------------------------------------------------------------
	//Visits data
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	parseCSV(line, csvData);
	
	numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System error during Visits import. Ignoring.");
		numberOfRecords = 0;
	}
	
	VisitListT * lastVisitRecord = malloc(sizeof(VisitListT));
	
	if(lastVisitRecord == NULL) {
		//Malloc error
	}
	
	VisitListT * firstVisitRecord = lastVisitRecord;
	
	for(i = 0; i < numberOfRecords; i++) {
		if(fgets(line, 500, userRecords) == NULL) {
			//Error during reading
		}
		parseCSV(line, csvData);
		
		VisitT * record = malloc(sizeof(VisitT));
		
		if(record == NULL) {
			//Malloc error
		}
		
		const int heartRate = (int) strtol(csvData[0], NULL, 10);
		if(heartRate == 0) {
			printf("System error during Visit import");
			record->heartRate = -1;
		}
		else {
			record->heartRate = heartRate;
		}
		
		const int bloodPressure = (int) strtol(csvData[1], NULL, 10);
		if(bloodPressure == 0) {
			printf("System error during Visit import");
			record->bloodPressure = -1;
		}
		else {
			record->bloodPressure = bloodPressure;
		}
		
		strncpy(record->visitDateTime, csvData[2], 19);
		strncpy(record->personSeen, csvData[3], 33);
		
		lastVisitRecord->item = record;
		lastVisitRecord->next = malloc(sizeof(VisitT));
		
		if(lastVisitRecord->next == NULL) {
			//Malloc error
		}
		
		lastVisitRecord = lastVisitRecord->next;
	}
	
	patient->visits = firstVisitRecord;
	
	//---------------------------------------------------------------------------------
	//Test Result data
	
	if(fgets(line, 500, userRecords) == NULL) {
		//Error during reading
	}
	parseCSV(line, csvData);
	
	numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System error during Test Results import. Ignoring.");
		numberOfRecords = 0;
	}
	
	TestResultListT * lastTestRecord = malloc(sizeof(TestResultListT));
	
	if(lastTestRecord == NULL) {
		//Malloc error;
	}
	
	TestResultListT * firstTestRecord = lastTestRecord;
	
	for(i = 0; i < numberOfRecords; i++) {
		if(fgets(line, 500, userRecords) == NULL) {
			//Error during reading
		}
		parseCSV(line, csvData);
		
		TestResultT * record = malloc(sizeof(TestResultT));
		
		if(record == NULL) {
			//Malloc error
		}
		
		strncpy(record->testName, csvData[0], 30);
		strncpy(record->testResults, csvData[1], 120);
		
		lastTestRecord->item = record;
		lastTestRecord->next = malloc(sizeof(TestResultT));
		
		if(lastTestRecord->next == NULL) {
			//Malloc error;
		}
		
		lastTestRecord = lastTestRecord->next;
	}
	
	patient->testResults = firstTestRecord;
	
	//I think we're done here.
	patientCache->item = patient;
	patientCache->next = malloc(sizeof(PatientCacheT));
	
	if(patientCache->next == NULL) {
		//Error;
	}
	
	fclose(userRecords);
	
	return patient;
}