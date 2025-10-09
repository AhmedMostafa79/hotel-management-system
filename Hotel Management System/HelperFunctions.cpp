#include "HelperFunctions.h"
#include <iostream>
#include <limits>

// use std:: explicitly in implementation

// Helper Functions Definitions
int getValidatedInt(const std::string& prompt) {
	int value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;

		if (std::cin.fail()) {
			std::cout << "\t\tInvalid input. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}

double getValidatedDouble(const std::string& prompt) {
	double value;
	while (true) {
	std::cout << prompt;
	std::cin >> value;

		if (std::cin.fail()) {
			std::cout << "\t\tInvalid input. Please enter a number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}

int readRangeInt(const int& low, const int& high) {
	while (true) {
		int num = getValidatedInt("\n\t\tEnter number in range " + std::to_string(low) + " - " + std::to_string(high) + " : ");
		std::cout << '\n';
		if (low <= num && num <= high) {
			return num;
		}
		std::cout << "\n\t\tInvalid number! Please try again.\n";
	}
}

int showOuterReadMenu(const std::string& menu_name, const std::vector<std::string>& choices) {
	std::cout << "\n\n\t***** " << menu_name << " *****\n\n\n";
	for (int choice = 0; choice < static_cast<int>(choices.size()); choice++) {
		std::cout << "\t\tChoice " << choice + 1 << ". " << choices[choice] << '\n';
	}
	int choice = readRangeInt(1, static_cast<int>(choices.size()));
	return choice;
}

int showInnerReadMenu(const std::string& menu_name, const std::vector<std::string>& choices) {
	std::cout << "\n\t\t=== " << menu_name << " ===\n\n";
	for (int choice = 0; choice < static_cast<int>(choices.size()); choice++) {
		std::cout << "\t\t\tChoice " << choice + 1 << ". " << choices[choice] << '\n';
	}
	int choice = readRangeInt(1, static_cast<int>(choices.size()));
	return choice;
}

std::string toLowerCase(std::string s) {
	for (auto& i : s)
		i = static_cast<char>(std::tolower(static_cast<unsigned char>(i)));
	return s;
}