#pragma once

#include <iostream>

class Log
{
public:
	static void Space() { std::cout << std::endl; }

	template<typename T>
	static void Info(const std::string& message, T data) { std::cout << "[INFO]: " << message << ": " << data << std::endl; }
	static void Info(const std::string& message) { std::cout << "[INFO]: " << message << std::endl; }

	template<typename T>
	static void Warning(const std::string& message, T data) { std::cout << "[WARNING]: " << message << ": " << data << std::endl; }
	static void Warning(const std::string& message) { std::cout << "[WARNING]: " << message << std::endl; }

	template<typename T>
	static void Error(const std::string& message, T data) { std::cout << "[ERROR]: " << message << ": " << data << std::endl; }
	static void Error(const std::string& message) { std::cout << "[ERROR]: " << message << std::endl; }

	static void Profile(const std::string& message, float time_ms) { std::cout << "[PROFILE]: " << message << ": " << time_ms << " ms" << std::endl; }
};
