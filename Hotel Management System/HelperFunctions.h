#pragma once
#include <string>
#include <vector>

// Helper Functions Declarations
/**
 * @brief Prompts the user and validates integer input.
 * @param prompt The message to display to the user.
 * @return int The validated integer input from the user.
 * @details Continuously prompts the user until valid integer input is received.
 *          Handles all error cases including non-numeric input and buffer cleanup.
 * @note Uses robust input validation with full buffer clearing to prevent
 *       any residual characters from affecting subsequent input operations.
 */
int getValidatedInt(const std::string& prompt);

/**
 * @brief Prompts the user and validates floating-point input.
 * @param prompt The message to display to the user.
 * @return double The validated double input from the user.
 * @details Continuously prompts the user until valid numeric input is received.
 *          Handles all error cases including non-numeric input and buffer cleanup.
 * @note Uses the same robust validation pattern as getValidatedInt() for consistency.
 */
double getValidatedDouble(const std::string& prompt);

/**
 * @brief Validates that an integer falls within a specified range.
 * @param low The lower bound of the valid range (inclusive).
 * @param high The upper bound of the valid range (inclusive).
 * @return int The validated integer within the specified range.
 * @details Uses getValidatedInt() for base validation, then checks range constraints.
 *          Provides specific error feedback for out-of-range values.
 */
int readRangeInt(const int& low, const int& high);

/**
 * @brief Displays a menu and returns the user's validated selection.
 * @param menu_name The title to display for the menu.
 * @param choices Vector of strings representing the menu options.
 * @return int The user's selection (1-based index corresponding to the choices vector).
 * @details Presents a formatted menu with numbered options and uses readInt()
 *          to ensure the selection is valid for the given choices.
 * @note The return value ranges from 1 to choices.size() (inclusive).
 */
int showOuterReadMenu(const std::string& menu_name, const std::vector<std::string>& choices);

//same as showOuterReadMenu but with different decoration.
int showInnerReadMenu(const std::string& menu_name, const std::vector<std::string>& choices);
/**
 * @brief Converts a string to lowercase letters.
 * @param s a string
 * @return string the converted string
 */
std::string toLowerCase(std::string s);