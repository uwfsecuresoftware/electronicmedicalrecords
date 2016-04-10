#include <string>

#ifndef MEDICATION_H
#define MEDICATION_H
class Medication {
	std::string medicationName;
	int dosage;
	std::string frequency;
	std::string prescribingDoctor;
	public:
		Medication(std::string name, int dose, std::string freq, std::string doc);
		Medication();
		
		std::string getName();
		void setName(std::string name);
		
		int getDosage();
		void setDosage(int dose);
		
		std::string getFrequency();
		void setFrequency(std::string freq);
		
		std::string getPrescribingDoctor();
		void setPrescribingDoctor(std::string doc);
};

#endif