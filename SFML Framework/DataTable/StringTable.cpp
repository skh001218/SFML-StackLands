#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load()
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);
		if (it != table.end())
		{
			std::cout << "��Ʈ�� ���̺� Ű �ߺ�!" << std::endl;
			continue;
		}

		for (int j = 0; j < (int)Languages::Count; ++j)
		{
			auto& vec = table[strings[0]];
			vec.push_back(converter.from_bytes(strings[j + 1]));
		}
	}

	for (auto& pair : table)
	{
		std::cout << pair.first << ": ";
		for (auto& s : pair.second)
		{
			std::wcout << s << " ";
		}
		std::cout << std::endl;
	}

	return false;
}

void StringTable::Release()
{
	table.clear();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	return Get(id, Variables::currentLang);
}

const std::wstring& StringTable::Get(const std::string& id, Languages lang)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return (find->second)[(int)lang];
}
