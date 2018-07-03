#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::istream_iterator;
using std::ostream_iterator;
using std::vector;

int main()
{
	istream_iterator<int> in(ref(cin)),eof;
	ostream_iterator<int> out(ref(cout)," ");
	vector<int> vecInt;
	auto bIter = back_inserter(vecInt);
	
	unique_copy(in,eof,bIter);
	sort(vecInt.begin(),vecInt.end());
	auto end_unque = unique(vecInt.begin(),vecInt.end());
	vecInt.erase(end_unque,vecInt.end());
	for_each(vecInt.cbegin(),vecInt.cend(),[&](int a){*out = a;});
	cout<<endl;
}