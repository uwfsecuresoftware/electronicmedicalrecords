#include "medication.h"

Medication::Medication() {
	medicationName = "";
	dosage = 0;
	frequency = "";
	prescribingDoctor = "";
}

Medication::Medication(std::string name, int dose, std::string freq, std::string doc) {
	medicationName = name;
	dosage = dose;
	frequency = freq;
	prescribingDoctor = doc;
}

std::string Medication::getName() {
	return medicationName;
}

void Medication::setName(std::string name) {
	medicationName = name;
}

int Medication::getDosage() {
	return dosage;
}

void Medication::setDosage(int dose) {
	dosage = dose;
}

std::string Medication::getFrequency() {
	return frequency;
}

void Medication::setFrequency(std::string freq) {
	frequency = freq;
}

std::string Medication::getPrescribingDoctor() {
	return prescribingDoctor;
}

void Medication::setPrescribingDoctor(std::string doc) {
	prescribingDoctor = doc;
}