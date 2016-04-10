#include "user.h"

AccountType User::convertToAccountType(std::string type) {
	if(type == "nurse") {
		return nurse;
	}
	else if(type == "doctor") {
		return doctor;
	}
	else if(type == "administrator") {
		return administrator;
	}
	else {
		return patient;
	}
}


User::User() {
	uuid = "";
	username = "";
	password = "";
	name = "";
	type = patient;
	age = 0;
	smokes = false;
}

std::string User::getUUID() {
	return this->uuid;
}

void User::setUUID(std::string uuid) {
	this->uuid = uuid;
}

std::string User::getUsername() {
	return this->username;
}

void User::setUsername(std::string username) {
	this->username = username;
}

std::string User::getPassword() {
	return this->password;
}

void User::setPassword(std::string password) {
	this->password = password;
}

int User::getAge() {
	return this->age;
}

void User::setAge(int age) {
	this->age = age;
}

bool User::isSmoker() {
	return this->smokes;
}

void User::setSmoker(bool smoker) {
	this->smokes = smoker;
}

Medication * User::getMedicationList() {
	return this->medList;
}

std::string User::getName() {
	return this->name;
}

void User::setName(std::string name) {
	this->name = name;
}

AccountType User::getAccountType() {
	return this->type;
}

void User::setAccountType(AccountType type) {
	this->type = type;
}

std::string User::getGender() {
	return this->gender;
}

void User::setGender(std::string gender) {
	this->gender = gender;
}

bool User::allowedAccessTo(std::string uuid) {
	//Everyone has access to their own records.
	if(uuid == this->uuid) {
		return true;
	}
	
	//Patients, no matter what (we're ignoring the fact that families exist),
	//will not have access to anyone else's records.
	if(this->type == patient && uuid != this->uuid) {
		return false;
	}
	
	size_t i = 0;
	
	while(!accessAllowedTo[i].empty()) {
		if(accessAllowedTo[i] == uuid) {
			return true;
		}
	}
	
	return false;
}

void User::importData(rapidjson::Value &userMetadata, rapidjson::Document &userData) {
	//Username, password, and access information come from the metadata db
	
	if(userMetadata.HasMember("username")) {
		this->username = userMetadata["username"].GetString();
	}
	
	if(userMetadata.HasMember("password")) {
		this->password = userMetadata["password"].GetString();
	}
	
	if(userMetadata.HasMember("accessControl")) {
		rapidjson::Value &access = userMetadata["accessControl"];
		accessAllowedTo = new std::string[access.Size()];
		
		for(rapidjson::SizeType i = 0; i < access.Size(); i++) {
			accessAllowedTo[i] = access[i].GetString();
		}
	}
	
	if(userMetadata.HasMember("userType")) {
		std::string type = userMetadata["userType"].GetString();
		this->type = convertToAccountType(type);
	}
	
	//The rest of the information comes from the user-specific file
	//I really do not like having to build this kind of abstraction layer.
	
	if(userData.HasMember("name")) {
		this->name = userData["name"].GetString();
	}
	
	if(userData.HasMember("age")) {
		this->age = userData["age"].GetInt();
	}
	
	if(userData.HasMember("smokes")) {
		this->smokes = userData["smokes"].GetBool();
	}
	
	if(userData.HasMember("gender")) {
		this->gender = userData["gender"].GetString();
	}
}