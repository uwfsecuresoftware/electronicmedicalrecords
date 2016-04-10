#include "../datatypes/user.h"
#include <fstream>
#include <string>
#include <map>
#include "../rapidjson/document.h"

#ifndef DATABASE_H
#define DATABASE_H

class Database {
	rapidjson::Document data;
	std::map <std::string, User> users;
	
	private:
		User loadUser(std::string uuid, rapidjson::Document userMetadata);
		void loadOrCreateFile(std::string filename, std::ifstream &stream);
		std::string readEntireFile(std::ifstream &file);
	
	public:
		void loadDatabase();
		void getUserByUsername(std::string username);
		void getUserByUUID(std::string uuid);
};

#endif