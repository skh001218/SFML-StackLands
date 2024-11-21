#pragma once
#include "DataTable.h"

struct DataCombine
{
	std::string id;
	int count;
	std::vector<std::pair<std::string, int>> kinds;
	int time;
};

class CombineTable : public DataTable
{
public:
	static DataCombine Undefined;

protected:
	std::unordered_map<std::string, DataCombine> table;
	std::string filePath = "tables/combine_table.json";

public:
	CombineTable() : DataTable(DataTable::Types::Combine) { };
	~CombineTable() = default;

	bool Load() override;
	void Release() override;

	const DataCombine& Get(std::string id);
	const std::unordered_map<std::string, DataCombine>& Get();
};

