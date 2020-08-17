#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
	To use the config reader, take a look at the config data enum to know how the data is structured.
	Once you know, call ConfigReader::GetData, with the ConfigData enum as an argument, and the desired data 
	in a template parameter.

	Example:
	ConfigReader::GetData<const char*>(CfgName);
*/

template<typename T>
class ConfigKey
{
public:
	const char* name;
	T data;
};

static class ConfigReader
{
public:
	static void SetFloat(const char* name, float data);
	static void SetInt(const char* name, int data);

private:
};

