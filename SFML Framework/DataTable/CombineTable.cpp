#include "stdafx.h"
#include "CombineTable.h"
#include "json.hpp"

DataCombine CombineTable::Undefined;

bool CombineTable::Load()
{
	Release();
	std::ifstream f(filePath);
	json j = json::parse(f);

	std::cout << j.dump(4) << std::endl;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return true;
}

void StoreTable::Release()
{
	table.clear();
}

const DataStore& StoreTable::Get(std::string id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}