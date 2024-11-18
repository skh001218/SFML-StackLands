#include "stdafx.h"
#include "StoreTable.h"
#include "rapidcsv.h"

DataStore StoreTable::Undefined;

bool StoreTable::Load()
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		std::string id = row[0];
		if (table.find(id) != table.end())
		{
			//
			return false;
		}
		table[id].id = id;
		table[id].stringFind = converter.from_bytes(row[1]);
		table[id].stringNone = converter.from_bytes(row[2]);
		table[id].texture = row[3];
		table[id].pos = { std::stof(row[4]), std::stof(row[5]) };
		table[id].posStr = { std::stof(row[6]), std::stof(row[7]) };;
		table[id].origin = (Origins)std::stoi(row[8]);
		table[id].font = row[9];
		table[id].price = stoi(row[10]);
	}

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
