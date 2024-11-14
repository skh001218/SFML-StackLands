#pragma once
#include "DataTable.h"

struct DataStore
{
	std::string id;
	std::wstring stringFind;
	std::wstring stringNone;
	std::string texture;
	sf::Vector2f pos;
	sf::Vector2f posStr;
	Origins origin;
	std::string font;
};


class StoreTable : public DataTable
{
public:
	static DataStore Undefined;

protected:
	std::unordered_map<std::string, DataStore> table;
	std::string filePath = "tables/store_table.csv";

public:
	StoreTable() : DataTable(DataTable::Types::Store) { };
	~StoreTable() = default;

	bool Load() override;
	void Release() override;

	const DataStore& Get(std::string id);
};

