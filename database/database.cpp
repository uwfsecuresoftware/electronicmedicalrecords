#include "database.h"
#include "../headers/exceptions.h"

void Database::loadOrCreateFile(std::string filename, std::ifstream &file) {
	file.open(filename.c_str());
	
	if(!file.is_open()) {
		//If it, for some reason, isn't open, try to create the file.
		std::ofstream fileOutput (filename.c_str());
		
		if(!fileOutput.is_open()) {
			//Well shit, something is uber weird.
			throw ERR_IO_EXCEPTION;
		}
		
		//Write just the most basic JSON object, then close.
		fileOutput << "{}";
		fileOutput.close();
		
		//Open the file for reading... again.
		return loadOrCreateFile(filename, file);
	}
	
	return;
}

std::string Database::readEntireFile(std::ifstream &file) {
	std::string line;
	std::string wholeFile;
	
	while(getline(file, line)) {
		wholeFile.append(line);
	}
	
	return wholeFile;
}

void Database::loadDatabase() {
	std::string databaseFilename = "database.json";
	
	std::ifstream databaseFile;
	
	loadOrCreateFile(databaseFilename, databaseFile);
	std::string json = readEntireFile(databaseFile);
	databaseFile.close();
	
	data.Parse(json.c_str());
}

User Database::loadUser(std::string uuid, rapidjson::Document userMetadata) {
	std::string userFilename = "records/";
	userFilename.append(uuid);
	userFilename.append(".json");
	
	std::ifstream userData;
	
	loadOrCreateFile(userFilename, userData);
	std::string json = readEntireFile(userData);
	userData.close();
	
	rapidjson::Document doc;
	doc.Parse(json.c_str());
	
	if(!doc.HasMember("name")) {
		//This means that the file was just created.
		User * user = new User();
		return *user;
	}
	
	User * user = new User();
	
	user->setUUID(uuid);
	
	user->importData(userMetadata["uuid"], doc);
	
	return *user;
}