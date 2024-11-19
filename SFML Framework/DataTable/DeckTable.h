#pragma once
#include "DataTable.h"

struct DataDeck
{
	int count;
	std::string texture;
	std::vector<std::vector<std::pair<std::string, float>>> deckList;
};


class DeckTable : public DataTable
{
public:
	static DataDeck Undefined;

protected:
	std::unordered_map<std::string, DataDeck> table;
	std::string filePath = "tables/new world_deck.csv";

public:
	DeckTable() : DataTable(DataTable::Types::Deck) { };
	~DeckTable() = default;

	bool Load() override;
	void Release() override;

	void SetFilePath(int order);

	const DataDeck& Get(std::string id);
};

