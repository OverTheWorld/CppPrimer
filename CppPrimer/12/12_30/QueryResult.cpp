#include "QueryResult.h"

using std::endl;

QueryResult::QueryResult(std::shared_ptr<std::vector<std::string>> ptrFile, std::shared_ptr<std::set<size_t>> ptrResultSet) 
:m_ptrFile(ptrFile), m_ptrResultSet(ptrResultSet)
{
}


QueryResult::~QueryResult()
{
}

std::ostream& print(std::ostream &os, QueryResult qr)
{
	os << "element occurs " << qr.m_ptrResultSet->size() << ((qr.m_ptrResultSet->size() == 1) ? "time" : "times") << endl;
	for_each(qr.m_ptrResultSet->cbegin(), qr.m_ptrResultSet->cend(),
		[&os,&qr](size_t num)
		{
			os << "\t(line " << num << ") " << (*qr.m_ptrFile)[num-1] << endl;
		}
	);
	return os;
}