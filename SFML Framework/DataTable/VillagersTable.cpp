#include "stdafx.h"
#include "VillagersTable.h"
#include "rapidcsv.h"

DataVillagers VillagersTable::Undefined;

bool VillagersTable::Load()
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
			return false;
		}

		table[id].id = id;
		table[id].health = stoi(row[1]);
		table[id].attackSpeed = stoi(row[2]);
		table[id].hitChance = stof(row[3]);
		table[id].damage = stoi(row[4]);
		table[id].foodEat = stoi(row[5]);
		table[id].iconTex = row[6];
		table[id].name = converter.from_bytes(row[7]);
	}

	return true;
}

void VillagersTable::Release()
{
	table.clear();
}

const DataVillagers& VillagersTable::Get(std::string id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}
