#pragma once
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include "Engine/Core/MiniginPCH.h"
#include "Engine/Helpers/Logger.h"
#include "Level.h"

using namespace MyEngine;
class LevelParser final
{
public:
	static void ParseFile(const std::string& levelPath, const std::string& enemyPath, std::vector<level>& levels)
	{
		UNREFERENCED_PARAMETER(levels);
		std::regex fileTypeRegex{ ".+\\.dat$" };

		std::ifstream levelFile;
		std::ifstream enemyFile;
		char c;

		if (!std::regex_match(levelPath, fileTypeRegex))
		{
			Logger::LogError("LevelData file is not a .dat file!");
			return;
		}

		if (!std::regex_match(enemyPath, fileTypeRegex))
		{
			Logger::LogError("EnemyData file is not a .dat file!");
			return;
		}

		levelFile.open(levelPath, std::ios::binary);
		if (!levelFile.is_open())
		{
			Logger::LogError("File [" + levelPath + "] could not be opened!");
			return;
		}
		enemyFile.open(enemyPath, std::ios::binary);
		if (!levelFile.is_open())
		{
			Logger::LogError("File [" + enemyPath + "] could not be opened!");
			return;
		}
		for (int levelCounter{};levelCounter <100;levelCounter++)
		{
			levels.push_back(level());
			level& currentLevel = levels.back();
			for (size_t lineCounter{}; lineCounter < 25; lineCounter++)
			{
				currentLevel.first.push_back(line());
				line& currentLine = currentLevel.first.back();
				for (size_t charCounter{}; charCounter < 4; charCounter++)
				{
					levelFile.read((char*)&c, sizeof(char));
					int number = 0b10000000;
					for (size_t cellCounter{}; cellCounter < 8; cellCounter++)
					{

						currentLine.push_back(c & number);
						number = number >> 1;
					}
				}
			}
			char first;
			enemyFile.read((char*)&first, sizeof(char));
			while (first != 0)
			{
				char second;
				char third;
				enemyFile.read((char*)&second, sizeof(char));
				enemyFile.read((char*)&third, sizeof(char));

				currentLevel.second.push_back(Enemy());
				currentLevel.second.back().Type = EnemyType( first & 0b00000111);
				currentLevel.second.back().Col = int((first >> 3) & 0b00011111);

				currentLevel.second.back().Row = int((second >> 3) & 0b00011111);
				currentLevel.second.back().Delay = 0.017f * int((third << 1) & 0b00111111);

				enemyFile.read((char*)&first, sizeof(char));
			}
		}
		levelFile.close();
		enemyFile.close();
		levels.pop_back();
	}
};