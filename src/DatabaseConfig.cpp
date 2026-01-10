#include "DatabaseConfig.h"
DatabaseConfig ::DatabaseConfig(
    const std::string& schema, 
    const std::string& server, 
    const std::string& username,
    const std::string& password):
	schema(schema),server(server),username(username),password(password) {}

const std::string& DatabaseConfig::getSchema()const {
	return schema;
}
const std::string& DatabaseConfig::getServer()const {
	return server;
}
const std::string& DatabaseConfig::getUsername()const {
	return username;
}
const std::string& DatabaseConfig::getPassword()const {
	return password;
}
#include "DatabaseConfig.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

DatabaseConfig DatabaseConfig::loadFromFile(const std::string& file) {
    std::ifstream configFile(file);

    if (!configFile.is_open()) {
        throw std::runtime_error("Cannot open config file: " + file);
    }

    std::string line;
    if (!std::getline(configFile, line)) {
        throw std::runtime_error("Config file is empty: " + file);
    }

    // Split by commas
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string part;

    while (std::getline(ss, part, ',')) {
        parts.push_back(part);
    }

    // Check we have exactly 4 parts
    if (parts.size() != 4) {
        throw std::runtime_error("Invalid config format. Expected: schema,server,username,password");
    }

    std::string schema = parts[0];
    std::string server = parts[1];
    std::string username = parts[2];
    std::string password = parts[3];

    configFile.close();

    return DatabaseConfig(schema, server, username, password);
}
