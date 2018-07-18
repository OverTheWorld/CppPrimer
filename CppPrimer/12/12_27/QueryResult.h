#pragma once
#include<iostream>
#include"TextQuery.h"
using std::ostream;
using std::pair;
using std::endl;
using std::cout;
using std::cin;

class QueryResult
{
public:
	QueryResult();
	~QueryResult();
	void runQueries(ifstream &ifs);
	void print(ostream &os,shared_ptr<map<size_t,const string*>> maplineToWords);
};

