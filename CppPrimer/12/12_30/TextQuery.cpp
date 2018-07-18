#include "QueryResult.h"
#include<sstream>

using std::ifstream;
using std::vector;
using std::string;
using std::map;
using std::set;
using std::shared_ptr;
using std::istringstream;
using std::make_shared;

TextQuery::TextQuery(ifstream &ifs) :m_ptrFile(make_shared<vector<string>>()), m_ptrMap(make_shared<map<string,shared_ptr<set<size_t>>>>())
{
	istringstream iss;
	string line, strTemp;
	size_t lineNum = 1;
	while (getline(ifs, line))
	{
		m_ptrFile->push_back(line);
		iss.str(line);
		while (iss >> strTemp)
		{
			auto &pSet = (*m_ptrMap)[strTemp];
			if (pSet == nullptr)
				pSet = make_shared<set<size_t>>();
			pSet->insert(lineNum);
		}
		++lineNum;
		iss.clear();
	}
}


TextQuery::~TextQuery()
{
}

QueryResult TextQuery::query(const string &str)const 
{
	static QueryResult QRnull(m_ptrFile,make_shared<set<size_t>>());
	auto iter = m_ptrMap->find(str);
	if (iter == m_ptrMap->end())
		return QRnull;
	return QueryResult(m_ptrFile, iter->second);
}