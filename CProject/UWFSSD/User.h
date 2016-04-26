#ifndef USER_H
#define USER_H

#define true 1
#define false 0

typedef int bool;

//---------------------------------------------------------------------
typedef struct VisitT {
	int heartRate;
	int bloodPressure;
	char visitDateTime[20];
	//Following is a UUID of the person in the system
	char personSeen[33];
} VisitT;

typedef struct VisitListT {
	VisitT * item;
	struct VisitListT * next;
} VisitListT;

//---------------------------------------------------------------------

typedef struct MedicationT {
	char name[40];
	int dosage;
	char prescribingPerson[33];
} MedicationT;

typedef struct MedicationListT {
	MedicationT * item;
	struct MedicationListT * next;
} MedicationListT;

typedef struct AllergyListT {
	MedicationT * item;
	struct AllergyListT * next;
} AllergyListT;

//---------------------------------------------------------------------

typedef struct ImmunizationT {
	char name[40];
	char datePerformed[20];
	char performingPerson[33];
} ImmunizationT;

typedef struct ImmunizationListT {
	ImmunizationT * item;
	struct ImmunizationListT * next;
} ImmunizationListT;

//---------------------------------------------------------------------

typedef struct {
	char name[40];
	char policyNumber[30];
} InsuranceT;

//---------------------------------------------------------------------

typedef struct TestResultT {
	char testName[30];
	char testResults[120];
} TestResultT;

typedef struct TestResultListT {
	TestResultT * item;
	struct TestResultListT *next;
} TestResultListT;

//---------------------------------------------------------------------


typedef struct PatientT {
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

typedef struct PatientCacheT {
	PatientT * item;
	struct PatientCacheT * next;
} PatientCacheT;

PatientT * fetchPatient(char * uuid);
void displayPatient(char *);
void exportUser(PatientT * patient);
void editPatient(char *);
void exportShitData(char * uuid);

#endif
