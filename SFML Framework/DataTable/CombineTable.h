#pragma once
#include "DataTable.h"

struct DataCombine
{

};

class CombineTable : public DataTable
{
public:
	static DataCombine Undefined;

protected:
	std::unordered_map<std::string, DataCombine> table;
	std::string filePath = "tables/store_table.csv";

public:
	CombineTable() : DataTable(DataTable::Types::Combine) { };
	~CombineTable() = default;

	/*bool Load() override;
	void Release() override;

	const DataCombine& Get(std::string id);*/
};

