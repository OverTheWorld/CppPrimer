#pragma once
#include<fstream>
#include<map>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<memory>

class QueryResult;

class TextQuery
{
public:
	TextQuery(std::ifstream &ifs);
	~TextQuery();
	QueryResult query(const std::string &str)const;
private:
	std::shared_ptr<std::vector<std::string>> m_ptrFile;
	std::shared_ptr<std::map<std::string, std::shared_ptr<std::set<size_t>>>> m_ptrMap;
};

