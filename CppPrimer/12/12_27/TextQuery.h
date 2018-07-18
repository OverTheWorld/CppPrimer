#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<memory>
#include<algorithm>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::shared_ptr;
using std::make_shared;

class TextQuery
{
	vector<string> vecText;
	map<string, set<size_t>> mapWordToLine;
	shared_ptr<map<size_t, const string*>> pMapQueryResult;
public:
	TextQuery(ifstream &ifs);
	~TextQuery();
	shared_ptr<map<size_t, const string*>> query(const string &str);
};

