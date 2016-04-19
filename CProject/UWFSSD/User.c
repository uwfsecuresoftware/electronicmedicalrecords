#include "User.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

PatientCacheT * patientCache = NULL

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
	PatientCacheT currentRecord = patientCache;
	
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
	fgets(line, 500, userRecords);
	
	PatientT * patient = malloc(sizeof(PatientT));
	
	if(feof(userRecords) && (line[0] == '\0' || line[0] == ' ' || line[1] == '\0')) {
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
	fgets(line, 500, userRecords);
	parseCSV(line, csvData);
	
	InsuranceT * insurance = malloc(sizeof(InsuranceT));
	strncpy(insurance->name, csvData[0], 40);
	strncpy(insurance->policyNumber, csvData[1], 30);
	
	patient->insurance = insurance;
	
	//--------------------------------------------------------------------------------
	//Immunization data
	fgets(line, 500, userRecords);
	parseCSV(line, csvData);
	
	int numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System errored during Immunization import. Ignoring.");
		numberOfRecords = 0;
	}
	
	int i = 0;
	ImmunizationListT * lastRecordImmu = malloc(sizeof(ImmunizationListT));
	ImmunizationListT * firstRecordImmu = lastRecordImmu;
	for(i = 0; i < numberOfRecords; i++) {
		fgets(line, 500, userRecords);
		parseCSV(line, csvData);
		
		ImmunizationT * record = malloc(sizeof(ImmunizationT));
		strncpy(record->name, csvData[0], 40);
		strncpy(record->datePerformed, csvData[1], 20);
		strncpy(record->performingPerson, csvData[2], 33);
		
		lastRecordImmu->item = record;
		lastRecordImmu->next = malloc(sizeof(ImmunizationListT));
		lastRecordImmu = lastRecordImmu->next;
	}
	
	patient->immunizations = firstRecordImmu;
	
	
	//--------------------------------------------------------------------------------
	//Medication data
	fgets(line, 500, userRecords);
	parseCSV(line, csvData);
	
	int numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System errored during Medication import. Ignoring.");
		numberOfRecords = 0;
	}
	
	MedicationListT * lastRecordMedi = malloc(sizeof(MedicationListT));
	MedicationListT * firstRecordMedi = lastRecordMedi;
	for(i = 0; i < numberOfRecords; i++) {
		fgets(line, 500, userRecords);
		parseCSV(line, csvData);
		
		MedicationT * record = malloc(sizeof(MedicationT));
		strncpy(record->name, csvData[0], 40);
		
		int dosage = (int) strtol(csvData[1], NULL, 10);
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
		lastRecordMedi = lastRecordMedi->next;
	}
	
	patient->medications = firstRecordMedi;
	
	//---------------------------------------------------------------------------------
	//Visits data
	fgets(line, 500, userRecords);
	parseCSV(line, csvData);
	
	int numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System error during Visits import. Ignoring.");
		numberOfRecords = 0;
	}
	
	VisitListT * lastVisitRecord = malloc(sizeof(VisitListT));
	VisitListT * firstVisitRecord = lastVisitRecord;
	
	for(i = 0; i < numberOfRecords; i++) {
		fgets(line, 500, userRecords);
		parseCSV(line, csvData);
		
		VisitT * record = malloc(sizeof(VisitT));
		
		int heartRate = (int) strtol(csvData[0], NULL, 10);
		if(heartRate == 0) {
			printf("System error during Visit import");
			record->heartRate = -1;
		}
		else {
			record->heartRate = heartRate;
		}
		
		int bloodPressure = (int) strtol(csvData[1], NULL, 10);
		if(bloodPressure == 0) {
			printf("System error during Visit import");
			record->bloodPressure = -1;
		}
		else {
			record->bloodPressure = bloodPressure;
		}
		
		strncpy(record->visitDateTime, csvData[2], 19);
		strncpy(record->personSeen, csvData[3], 33);
		
		listVisitRecord->item = record;
		lastVisitRecord->next = malloc(sizeof(VisitT));
		lastVisitRecord = lastVisitRecord->next;
	}
	
	patient->visits = firstVisitRecord;
	
	//---------------------------------------------------------------------------------
	//Test Result data
	
	fgets(line, 500, userRecords);
	parseCSV(line, csvData);
	
	int numberOfRecords = (int) strtol(csvData[1], NULL, 10);
	if(numberOfRecords == 0) {
		printf("System error during Test Results import. Ignoring.");
		numberOfRecords = 0;
	}
	
	TestResultListT * lastTestRecord = malloc(sizeof(TestResultListT));
	TestResultListT * firstTestRecord = lastTestRecord;
	
	for(i = 0; i < numberOfRecords; i++) {
		fgets(line, 500, userRecords);
		parseCSV(line, csvData);
		
		TestResultT * record = malloc(sizeof(TestResultT));
		
		strncpy(record->testName, csvData[0], 30);
		strncpy(record->testResults, csvData[1], 120);
		
		lastTestRecord->item = record;
		lastTestRecord->next = malloc(sizeof(TestResultT));
		lastTestRecord = lastTestRecord->next;
	}
	
	patient->testResults = firstTestRecord;
	
	//I think we're done here.
	patientCache->item = patient;
	paatientCache->next = malloc(sizeof(PatientCacheT));
	
	return patient;
}