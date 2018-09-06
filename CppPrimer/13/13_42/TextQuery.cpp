#include"TextQuery.h"
#include<fstream>
#include<sstream>
using std::string;
using std::ifstream;
using std::getline;
using std::map;
using std::set;
using std::shared_ptr;
using std::make_shared;
using std::istringstream;

TextQuery::TextQuery(const string &strFileName):
	sptrFile(make_shared<StrVec>()),sptrMap(make_shared<map<string,shared_ptr<set<size_t>>>>())
{
	ifstream ifs(strFileName);
	string line,strtemp;
	istringstream iss;
	size_t lineNum = 0;
	while (getline(ifs, line))
	{
		sptrFile->push_back(line);
		iss.str(line);
		while (iss >> strtemp)
		{
			if (sptrMap->find(strtemp) == sptrMap->end())
			{
				(*sptrMap)[strtemp] = make_shared<set<size_t>>();
			}
			sptrMap->at(strtemp)->insert(lineNum);
		}
		iss.clear();
		++lineNum;
	}
}

TextQuery::~TextQuery()
{

}

QueryResult TextQuery::query(const string &strWords)
{
	shared_ptr<set<size_t>> sptrSet = make_shared<set<size_t>>();
	if (sptrMap->find(strWords) != sptrMap->end())
		sptrSet = sptrMap->at(strWords);
	return QueryResult(sptrFile, sptrSet);
}