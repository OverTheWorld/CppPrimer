#include "TextQuery.h"


TextQuery::TextQuery(ifstream &ifs):pMapQueryResult(make_shared<map<size_t,const string*>>())
{
	string line, str;
	istringstream iss;
	size_t lineNum = 0;
	while (getline(ifs, line))
	{
		vecText.push_back(line);
		iss.str(line);
		while (iss >> str)
		{
			mapWordToLine[str].insert(lineNum);
		}
		++lineNum;
		iss.clear();
	}
}


TextQuery::~TextQuery()
{
}

shared_ptr<map<size_t, const string *>> TextQuery::query(const string &str)
{
	pMapQueryResult->clear();
	auto iter = mapWordToLine.find(str);
	if (iter == mapWordToLine.end())
		return nullptr;
	for_each(iter->second.cbegin(),iter->second.cend(),
		[this](size_t lineNum)
		{
			(*pMapQueryResult)[lineNum] = &(vecText.at(lineNum));
		}
	);
	return pMapQueryResult;
}