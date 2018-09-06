#include"QueryResult.h"
#include<algorithm>

using std::ostream;
using std::endl;
using std::for_each;

ostream& Print(ostream &out, const QueryResult &t)
{
	out << "element occurs " << t.sptrSet->size() << " times:" << endl;
	for_each(t.sptrSet->begin(), t.sptrSet->end(), [&](size_t i) 
	{
		out << "\t(line " << i << ") " << t.sptrStrVec->at(i) << endl;
	}
	);
	return out;
}