#pragma once
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include "Engine/Core/MiniginPCH.h"
#include "Engine/Helpers/Logger.h"
typedef std::vector<bool> line;
typedef std::vector<line> level;

using namespace MyEngine;
class LevelParser final
{
public:
	static void ParseFile(const std::string& path, std::vector<level>& levels)
	{
		UNREFERENCED_PARAMETER(levels);
		std::regex fileTypeRegex{ ".+\\.dat$" };

		std::ifstream file;
		char c;

		if (!std::regex_match(path, fileTypeRegex))
		{
			Logger::GetInstance()->LogError("File is not a .dat file!");
			return;
		}

		file.open(path, std::ios::binary);
		if (!file.is_open())
		{
			Logger::GetInstance()->LogError("File [" + path + "] could not be opened!");
			return;
		}
		while (!file.eof())
		{
			levels.push_back(level());
			level& currentLevel = levels.back();
			for (size_t lineCounter{}; lineCounter < 25; lineCounter++)
			{
				currentLevel.push_back(line());
				line& currentLine = currentLevel.back();
				for (size_t charCounter{}; charCounter < 4; charCounter++)
				{
					file.read((char*)&c, sizeof(char));
					for (size_t cellCounter{}; cellCounter < 8; cellCounter++)
					{
						currentLine.push_back(c & 1);
						c = c >> 1;
					}
				}
			}
		}
		file.close();
	}
};