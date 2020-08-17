#pragma once
#include "IO.h"

namespace Debug
{
	//Writes msg to output.log, and std::cout.
	static void Log(const std::stringstream& msg)
	{
		std::ofstream log;
		log.open("output.log");

		if (log.is_open())
		{
			log << msg.rdbuf() << std::endl;
		}
		log.close();
	}

	static void Log(const char* msg)
	{
		std::ofstream log;
		log.open("output.log");

		if (log.is_open())
		{
			log << msg << std::endl;
		}
		log.close();
	}
};

