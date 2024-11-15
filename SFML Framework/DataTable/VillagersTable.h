#pragma once
#include "DataTable.h"

struct DataVillagers
{
	std::string id;
	int		health;
	float	attackSpeed;
	float	hitChance;
	int		damage;
	int		foodEat;
	std::string iconTex;
	std::wstring name;
};


class VillagersTable : public DataTable
{
public:
	static DataVillagers Undefined;

protected:
	std::unordered_map<std::string, DataVillagers> table;
	std::string filePath = "tables/villagers_table.csv";

public:
	VillagersTable() : DataTable(DataTable::Types::Villagers) { };
	~VillagersTable() = default;

	bool Load() override;
	void Release() override;

	const DataVillagers& Get(std::string id);
};

