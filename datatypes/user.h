#include "medication.h"
#include "../rapidjson/document.h"

#ifndef USER_H
#define USER_H

enum AccountType {
	patient,
	nurse,
	doctor,
	administrator
};

class User {
	std::string uuid;
	std::string username;
	std::string password;
	std::string name;
	AccountType type;
	std::string * accessAllowedTo;
	int age;
	bool smokes;
	std::string gender;
	Medication * medList;
	
	private:
		AccountType convertToAccountType(std::string type);
	
	public:
		User();
		std::string getUUID();
		void setUUID(std::string uuid);
		
		std::string getUsername();
		void setUsername(std::string username);
		
		std::string getPassword();
		void setPassword(std::string password);
		
		int getAge();
		void setAge(int age);
		
		bool isSmoker();
		void setSmoker(bool smoker);
		
		std::string getName();
		void setName(std::string name);
		
		AccountType getAccountType();
		void setAccountType(AccountType type);
		
		Medication * getMedicationList();
		
		std::string getGender();
		void setGender(std::string gender);
		
		bool allowedAccessTo(std::string uuid);
		
		void importData(rapidjson::Value &userMetadata, rapidjson::Document &userData);
};

#endif