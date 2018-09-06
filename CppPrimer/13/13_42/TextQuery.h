#pragma once
#include<string>
#include<memory>
#include<set>
#include<map>
#include"StrVec.h"
#include"QueryResult.h"
class TextQuery
{
private:
	std::shared_ptr<StrVec> sptrFile;
	std::shared_ptr<std::map<std::string, std::shared_ptr<std::set<size_t>>>> sptrMap;
public:
	TextQuery(const std::string &strFileName);
	~TextQuery();
	QueryResult query(const std::string &strWords);
};

