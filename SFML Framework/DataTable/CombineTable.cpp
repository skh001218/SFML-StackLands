#include "stdafx.h"
#include "CombineTable.h"
#include "json.hpp"

DataCombine CombineTable::Undefined;

bool CombineTable::Load()
{
	Release();
	std::ifstream f(filePath);
	json j = json::parse(f);

	for (json::iterator it = j.begin(); it != j.end(); ++it) {

		std::string id = it.key();
		table[id].id = id;
		table[id].count = it.value()[0].at("count");
		auto temp = it.value()[1];
		for (auto itr = temp.begin(); itr != temp.end(); itr++)
		{
			table[id].kinds.push_back({ itr.key(), itr.value() });
		}
		table[id].time = it.value()[2].at("time");
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return true;
}

void CombineTable::Release()
{
	table.clear();
}

const DataCombine& CombineTable::Get(std::string id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}

const std::unordered_map<std::string, DataCombine>& CombineTable::Get()
{
	return table;
}
