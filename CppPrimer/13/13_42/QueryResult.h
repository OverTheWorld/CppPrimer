#pragma once
#include<set>
#include<string>
#include<memory>
#include<iostream>
#include"StrVec.h"
class QueryResult
{
	friend std::ostream& Print(std::ostream &out, const QueryResult &t);
private:
	std::shared_ptr<StrVec> sptrStrVec;
	std::shared_ptr<std::set<size_t>> sptrSet;
public:
	QueryResult(std::shared_ptr<StrVec> sptrstrvec,std::shared_ptr<std::set<size_t>> sptrset):sptrSet(sptrset),sptrStrVec(sptrstrvec) {};
	~QueryResult() {};

};
std::ostream& Print(std::ostream &out, const QueryResult &t);
