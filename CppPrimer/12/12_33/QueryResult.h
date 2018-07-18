#pragma once
#include"TextQuery.h"
class QueryResult
{
	friend std::ostream& print(std::ostream &os, const QueryResult &qr);
public:
	QueryResult(std::shared_ptr<std::vector<std::string>> ptrFile, std::shared_ptr<std::set<size_t>> ptrResultSet);
	~QueryResult();
	std::set<size_t>::iterator begin()const{ return m_ptrResultSet->begin(); }
	std::set<size_t>::iterator end()const{ return m_ptrResultSet->end(); }
	std::shared_ptr<std::vector<std::string>> get_File()const { return m_ptrFile; }
private:
	std::shared_ptr<std::vector<std::string>> m_ptrFile;
	std::shared_ptr<std::set<size_t>> m_ptrResultSet;
};

std::ostream& print(std::ostream &os, const QueryResult &qr);