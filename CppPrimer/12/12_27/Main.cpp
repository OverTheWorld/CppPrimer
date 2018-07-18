#include"QueryResult.h"

int main()
{
	ifstream ifs("QueryResult.cpp");
	QueryResult qr;
	qr.runQueries(ifs);
}