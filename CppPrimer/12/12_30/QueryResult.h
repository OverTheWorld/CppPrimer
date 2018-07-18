#pragma once
#include"TextQuery.h"
class QueryResult
{
	friend std::ostream& print(std::ostream &os, QueryResult qr);
public:
	QueryResult(std::shared_ptr<std::vector<std::string>> ptrFile, std::shared_ptr<std::set<size_t>> ptrResultSet);
	~QueryResult();
private:
	std::shared_ptr<std::vector<std::string>> m_ptrFile;
	std::shared_ptr<std::set<size_t>> m_ptrResultSet;
};

std::ostream& print(std::ostream &os, QueryResult qr);