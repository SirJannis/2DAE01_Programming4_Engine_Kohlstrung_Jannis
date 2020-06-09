#pragma once
#include <vector>

enum class EnemyType
{
	ZenChan = 0,
	Hidegons = 1,
	BaneBou = 2,
	Pulpul = 3,
	Monsta = 4,
	Drunk = 5,
	Mighta = 6,
	Invader = 7
};

struct Enemy
{
	EnemyType Type;
	int Row;
	int Col;
	float Delay;
};

typedef std::vector<bool> line;
typedef std::pair<std::vector<line>, std::vector<Enemy>> level;