#ifndef USER_H
#define USER_H

#define true 1
#define false 0

typedef int bool;

//---------------------------------------------------------------------
typedef struct {
	int heartRate;
	int bloodPressure;
	char visitDateTime[20];
	//Following is a UUID of the person in the system
	char personSeen[33];
} VisitT;

typedef struct {
	VisitT * item;
	struct VisitListT * next;
} VisitListT;

//---------------------------------------------------------------------

typedef struct {
	char name[40];
	int dosage;
	char prescribingPerson[33];
} MedicationT;

typedef struct {
	MedicationT * item;
	struct MedicationListT * next;
} MedicationListT;

typedef struct {
	MedicationT * item;
	struct AllergyListT * next;
} AllergyListT;

//---------------------------------------------------------------------

typedef struct {
	char name[40];
	char datePerformed[20];
	char performingPerson[33];
} ImmunizationT;

typedef struct {
	ImmunizationT * item;
	struct ImmunizationListT * next;
} ImmunizationListT;

//---------------------------------------------------------------------

typedef struct {
	char name[40];
	char policyNumber[30];
} InsuranceT;

//---------------------------------------------------------------------

typedef struct {
	char testName[30];
	char testResults[120];
} TestResultT;

typedef struct {
	TestResultT * item;
	struct TestResultListT *next;
} TestResultListT;

//---------------------------------------------------------------------


typedef struct {
	//8 + 4 + 4 + 4 + 8 + 1 for null termination 
	char uuid[33];
	char firstName[30];
	char lastName[30];
	bool smokes;
	char race[30];
	char gender[30];
	int age;
	char ssn[10];
	InsuranceT * insurance;
	char dateOfBirth[11];
	ImmunizationListT * immunizations;
	MedicationListT * medications;
	VisitListT * visits;
	TestResultListT * testResults;
} PatientT;

typedef struct {
	PatientT * item;
	struct PatientCacheT * next;
} PatientCacheT;

PatientT * fetchPatient(char * uuid);
void displayPatient(char *);
void editPatient(char *);

#endif
