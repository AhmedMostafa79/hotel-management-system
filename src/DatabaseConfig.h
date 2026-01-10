#pragma once
#include <string>

/**
 * @file DatabaseConfig.h
 * @brief Small value type carrying database connection parameters.
 *
 * The DatabaseConfig class encapsulates the minimum set of parameters
 * required to establish a database connection (schema, server, username,
 * and password). It also provides a convenience loader to read a config
 * line from a file.
 */

/**
 * @class DatabaseConfig
 * @brief Database connection configuration container.
 *
 * Instances of this class are simple, immutable containers used to pass
 * database connection information around the system. Use
 * DatabaseConfig::loadFromFile() to create an instance from a small
 * CSV-style file used by the application.
 */
class DatabaseConfig {
	std::string schema;   ///< Database schema (or database name)
	std::string server;   ///< Server address or hostname
	std::string username; ///< Username for authentication
	std::string password; ///< Password for authentication

public:
	/**
	 * @brief Construct a DatabaseConfig with explicit values.
	 * @param schema Database schema/name.
	 * @param server Server hostname or IP.
	 * @param username User name used to authenticate.
	 * @param password Password used to authenticate.
	 */
	DatabaseConfig(const std::string& schema, const std::string& server, const std::string& username, const std::string& password);

	/**
	 * @brief Get the configured schema (database name).
	 * @return const std::string& Reference to the schema string.
	 */
	const std::string& getSchema() const;

	/**
	 * @brief Get the configured server host/address.
	 * @return const std::string& Reference to the server string.
	 */
	const std::string& getServer() const;

	/**
	 * @brief Get the configured username.
	 * @return const std::string& Reference to the username string.
	 */
	const std::string& getUsername() const;

	/**
	 * @brief Get the configured password.
	 * @note Callers must ensure sensitive values are handled securely.
	 * @return const std::string& Reference to the password string.
	 */
	const std::string& getPassword() const;

	/**
	 * @brief Load a DatabaseConfig from a file.
	 *
	 * The function expects a small text file containing a single CSV line in
	 * the following order: schema,server,username,password.
	 *
	 * @param file Path to the configuration file to read.
	 * @return DatabaseConfig The parsed configuration instance.
	 */
	static DatabaseConfig loadFromFile(const std::string& file);
};