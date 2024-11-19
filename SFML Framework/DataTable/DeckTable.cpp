#include "stdafx.h"
#include "StoreTable.h"
#include "rapidcsv.h"

DataDeck DeckTable::Undefined;

bool DeckTable::Load()
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	auto data = doc.GetRow<std::string>(0);

	std::string id = "DECK";
	table[id].count = std::stoi(data[0]);
	table[id].texture = data[1];
	for (int i = 3; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		
		//if (table.find(id) != table.end())
		//{
		//	//
		//	return false;
		//}
		table[id].deckList.resize(5);
		table[id].deckList[0].push_back({row[0],std::stof(row[1])});
		table[id].deckList[1].push_back({row[2],std::stof(row[3])});
		table[id].deckList[2].push_back({row[4],std::stof(row[5])});
		table[id].deckList[3].push_back({row[6],std::stof(row[7])});
		table[id].deckList[4].push_back({row[8],std::stof(row[9])});
	}

	return true;
}

void DeckTable::Release()
{
	table.clear();
}

void DeckTable::SetFilePath(int order)
{
	switch (order)
	{
	case 0:
		filePath = "tables/new world_deck.csv";
		break;
	case 1:
		filePath = "tables/humble beginnings_deck.csv";
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
}

const DataDeck& DeckTable::Get(std::string id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}
