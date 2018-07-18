#include"QueryResult.h"


QueryResult::QueryResult()
{
}
QueryResult::~QueryResult()
{
}
void QueryResult::print(ostream &os, shared_ptr<map<size_t, const string*>> maplineToWords)
{
	if (maplineToWords == nullptr)
	{
		cout << "null pointer!" << endl;
		return;
	}
	cout << "element occurs " << maplineToWords->size() << endl;
	for_each(maplineToWords->cbegin(),maplineToWords->cend(),
		[&os](const pair<size_t, const string*> &par)
		{
			os << "\t (line " << par.first << " ) " << *(par.second) << endl;
		}
	);
}
void QueryResult::runQueries(ifstream &ifs)
{
	TextQuery tq(ifs);
	string str;
	while (true)
	{
		cout << "enter an words to search:" << endl;
		if (!(cin >> str) || str == "q")
			break;
		print(cout, tq.query(str));
	}
}